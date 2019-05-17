#include "../shared.hpp"

namespace shared::mem
{
	address_t find_ida_sig( const char* mod, const char* sig )
	{
		/// Credits: MarkHC
		static auto pattern_to_byte = []( const char* pattern )
		{
			auto bytes = std::vector<int>{};
			auto start = const_cast< char* >( pattern );
			auto end = const_cast< char* >( pattern ) + strlen( pattern );

			for ( auto current = start; current < end; ++current )
			{
				if ( *current == '?' )
				{
					++current;
					if ( *current == '?' )
						++current;
					bytes.push_back( -1 );
				}
				else
				{
					bytes.push_back( strtoul( current, &current, 16 ) );
				}
			}
			return bytes;
		};

		const auto module = GetModuleHandleA( mod );

		if ( module )
		{
			const auto dosHeader = PIMAGE_DOS_HEADER( module );
			const auto ntHeaders = PIMAGE_NT_HEADERS( reinterpret_cast< std::uint8_t* >( module ) + dosHeader->e_lfanew );

			const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
			auto patternBytes = pattern_to_byte( sig );
			const auto scanBytes = reinterpret_cast< std::uint8_t* >( module );

			const auto s = patternBytes.size();
			const auto d = patternBytes.data();

			if ( !sizeOfImage )
				return address_t( nullptr );

			for ( auto i = 0ul; i < sizeOfImage - s; ++i )
			{
				auto found = true;
				for ( auto j = 0ul; j < s; ++j )
				{
					if ( scanBytes[ i + j ] != d[ j ] && d[ j ] != -1 )
					{
						found = false;
						break;
					}
				}

				if ( found )
					return address_t( uintptr_t( &scanBytes[ i ] ) );
			}
		}

		return address_t( nullptr );
	}

	/// Go through multiple sigs incase 1 is invalid
	address_t find_ida_sig( const char* mod, const std::vector<const char*>& sigs )
	{
		/// TODO: maybe scan all sigs and check if they all match? 
		address_t dummy{};
		for ( auto sig : sigs )
			/// Check if address was found
			if ( dummy = find_ida_sig( mod, sig ) )
				break;

		/// No valid address found
		return address_t( nullptr );
	}

	address_t call_vfunc( address_t table, uint16_t index )
	{
		return table.to<address_t*>()->offset( 0x4 * index );
	}

	uint32_t get_vtable_length( address_t table )
	{
		auto length = uint32_t{};

		while ( table.as<uintptr_t*>()[ length ] >= 0x00010000 &&
				table.as<uintptr_t*>()[ length ] < 0xFFF00000 &&
				length < 1024 )
		{
			length++;
		}

		return length;
	}

	inline bool is_safe_address( address_t address )
	{
		/// Check for nullptr
		if ( !address )
			return false;

		/// Check if it's within relevant area
		if ( address < 0x1000 ||
			 address > 0xFFE0000 )
			return false;

		/// Get memory info
		static MEMORY_BASIC_INFORMATION32 info{};
		if ( !VirtualQuery( address.as<void*>(), reinterpret_cast< PMEMORY_BASIC_INFORMATION >(&info), sizeof(info)))
			return false;

		/// Check for base address pointer
		if ( !info.AllocationBase )
			return false;

		/// Check if page has been allocated memory
		if ( ! bitflag_t( info.State ).has_flag( MEM_COMMIT ) )
			return false;

		/// Check if we have access to the page memory
		if ( info.Protect == PAGE_NOACCESS
			 || bitflag_t( info.Protect ).has_flag( PAGE_GUARD ) )
			return false;

		/// Nice address
		return true;
	}
}