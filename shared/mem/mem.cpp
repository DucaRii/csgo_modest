#include "../shared.hpp"

namespace shared::mem
{
	address_t find_ida_sig( const char* mod, const char* sig )
	{
		/// Credits: MarkHC, although slightly modified by me and also documented

		static auto pattern_to_byte = []( const char* pattern )
		{
			/// Prerequisites
			auto bytes = std::vector<int>{};
			auto start = const_cast< char* >( pattern );
			auto end = const_cast< char* >( pattern ) + strlen( pattern );

			/// Convert signature into corresponding bytes
			for ( auto current = start; current < end; ++current )
			{
				/// Is current byte a wildcard? Simply ignore that that byte later
				if ( *current == '?' )
				{
					++current;

					/// Check if following byte is also a wildcard
					if ( *current == '?' )
						++current;

					/// Dummy byte
					bytes.push_back( -1 );
				}
				else
				{
					/// Convert character to byte on hexadecimal base
					bytes.push_back( strtoul( current, &current, 16 ) );
				}
			}
			return bytes;
		};

		const auto module_handle = GetModuleHandleA( mod );
		if ( !module_handle )
			return {};

		/// Get module information to search in the given module
		MODULEINFO module_info;
		GetModuleInformation( GetCurrentProcess(), reinterpret_cast< HMODULE >( module_handle ), &module_info, sizeof( MODULEINFO ) );

		/// The region where we will search for the byte sequence
		const auto image_size = module_info.SizeOfImage;

		/// Check if the image is faulty
		if ( !image_size )
			return {};

		/// Convert IDA-Style signature to a byte sequence
		auto pattern_bytes = pattern_to_byte( sig );

		const auto image_bytes = reinterpret_cast< byte* >( module_handle );

		const auto signature_size = pattern_bytes.size();
		const auto signature_bytes = pattern_bytes.data();

		/// Now loop through all bytes and check if the byte sequence matches
		for ( auto i = 0ul; i < image_size - signature_size; ++i )
		{
			auto byte_sequence_found = true;

			/// Go through all bytes from the signature and check if it matches
			for ( auto j = 0ul; j < signature_size; ++j )
			{
				if ( image_bytes[ i + j ] != signature_bytes[ j ] /// Bytes don't match
					 && signature_bytes[ j ] != -1 ) /// Byte isn't a wildcard either, WHAT THE HECK
				{
					byte_sequence_found = false;
					break;
				}
			}

			/// All good, now return the right address
			if ( byte_sequence_found )
				return address_t( uintptr_t( &image_bytes[ i ] ) );
		}

		/// Byte sequence wasn't found
		return {};
	}

	/// Go through multiple sigs incase 1 is invalid
	address_t find_ida_sig( const char* mod, const std::vector<const char*>& sigs )
	{
		/// TODO: maybe scan all sigs and check if they all match? 
		address_t dummy{};

		auto sigs_tried = uint32_t();

		for ( auto sig : sigs )
			/// Check if address was found
			if ( dummy = find_ida_sig( mod, sig ) )
				break;
			else
				LOG( fmt::format( "Failed to find signature {}/{} ( {} ), ", ++sigs_tried, sigs.size(), sig ) );

		/// No valid address found
		return dummy;
	}

	address_t find_fizz_sig( const char* mod, const char* sig )
	{
		static auto pattern_to_byte = []( const char* pattern )
		{
			/// Prerequisites
			auto bytes = std::vector<int>{};
			auto start = const_cast< char* >( pattern );
			auto end = const_cast< char* >( pattern ) + strlen( pattern );

			/// Convert signature into corresponding bytes
			for ( auto current = start; current < end; ++current )
			{
				/// Is current byte a wildcard? Simply ignore that that byte later
				if ( *current == '..' )
				{
					++current;

					/// Check if following byte is also a wildcard
					if ( *current == '..' )
						++current;

					/// Dummy byte
					bytes.push_back( -1 );
				}
				else
				{
					/// Convert character to byte on hexadecimal base
					bytes.push_back( strtoul( current, &current, 16 ) );
				}
			}
			return bytes;
		};

		const auto module_handle = GetModuleHandleA( mod );
		if ( !module_handle )
			return {};

		/// Get module information to search in the given module
		MODULEINFO module_info;
		GetModuleInformation( GetCurrentProcess(), reinterpret_cast< HMODULE >( module_handle ), &module_info, sizeof( MODULEINFO ) );

		/// The region where we will search for the byte sequence
		const auto image_size = module_info.SizeOfImage;

		/// Check if the image is faulty
		if ( !image_size )
			return {};

		/// Convert IDA-Style signature to a byte sequence
		auto pattern_bytes = pattern_to_byte( sig );

		const auto image_bytes = reinterpret_cast< byte* >( module_handle );

		const auto signature_size = pattern_bytes.size();
		const auto signature_bytes = pattern_bytes.data();

		/// Now loop through all bytes and check if the byte sequence matches
		for ( auto i = 0ul; i < image_size - signature_size; ++i )
		{
			auto byte_sequence_found = true;

			/// Go through all bytes from the signature and check if it matches
			for ( auto j = 0ul; j < signature_size; ++j )
			{
				if ( image_bytes[ i + j ] != signature_bytes[ j ] /// Bytes don't match
					 && signature_bytes[ j ] != -1 ) /// Byte isn't a wildcard either, WHAT THE HECK
				{
					byte_sequence_found = false;
					break;
				}
			}

			/// All good, now return the right address
			if ( byte_sequence_found )
				return address_t( uintptr_t( &image_bytes[ i ] ) );
		}

		/// Byte sequence wasn't found
		return {};
	}

	address_t find_fizz_sig( const char* mod, const std::vector<const char*>& sigs )
	{
		/// TODO: maybe scan all sigs and check if they all match? 
		address_t dummy{};

		auto sigs_tried = uint32_t();

		for ( auto sig : sigs )
			/// Check if address was found
			if ( dummy = find_fizz_sig( mod, sig ) )
				break;
			else
				LOG( fmt::format( "Failed to find signature {}/{} ( {} ), ", ++sigs_tried, sigs.size(), sig ) );

		/// No valid address found
		return dummy;
	}

	address_t get_vfunc( address_t table, uint16_t index )
	{
		return table.get<uintptr_t*>()[ index ];
	}

	uint32_t get_vtable_length( address_t table )
	{
		auto length = uint32_t{};

		/// Walk through every function until it is no longer valid
		for ( length = 0; table.cast<uintptr_t*>()[ length ]; length++ )
			if ( IS_INTRESOURCE( table.cast<uintptr_t*>()[ length ] ) )
				break;

		return length;
	}

	std::vector<std::wstring>& get_loaded_modules()
	{
		static std::vector<std::wstring> m_modules{};

		/// Was it already initialized?
		if ( m_modules.empty() )
		{
			/// Get Process Environment Block
			auto peb = reinterpret_cast< PEB* >( reinterpret_cast< TEB* >( __readfsdword( 0x18 ) )->ProcessEnvironmentBlock );
			if ( !peb || !peb->Ldr->InMemoryOrderModuleList.Flink )
				return m_modules;

			/// Get module list
			auto module_list = &peb->Ldr->InMemoryOrderModuleList;

			/// Loop through module list
			for ( auto i = module_list->Flink; i != module_list; i = i->Flink )
			{
				/// Current module list entry
				auto entry = CONTAINING_RECORD( i, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
				if ( !entry )
					continue;

				/// Strip module path
				auto path = std::wstring( entry->FullDllName.Buffer );
				auto module_name_begin = path.find_last_of( '\\' );
				if ( module_name_begin != std::wstring::npos )
					m_modules.push_back( path.substr( module_name_begin + 1 ) );
			}
		}
		return m_modules;
	}
}