#include "../shared.hpp"

namespace shared::mem
{
	std::vector<MODULEENTRY32> m_modules;

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
	address_t find_ida_sig( const char* mod, const std::vector<const char*> & sigs )
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

	std::vector<MODULEENTRY32>& get_loaded_modules()
	{
		/// Was it already initialized?
		if ( m_modules.empty() )
		{
			auto snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetCurrentProcessId() );
			if ( snapshot != INVALID_HANDLE_VALUE )
			{
				auto module_entry = MODULEENTRY32{ sizeof( MODULEENTRY32 ) };

				if ( Module32First( snapshot, &module_entry ) )
				{
					do
					{
						m_modules.push_back( module_entry);
					} while ( Module32Next( snapshot, &module_entry ) );
				}

				CloseHandle( snapshot );
			}
		}

		return m_modules;
	}
}