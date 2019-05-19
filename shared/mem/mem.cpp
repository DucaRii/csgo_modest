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
				return {};

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

		return {};
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
		return {};
	}

	address_t call_vfunc( address_t table, uint16_t index )
	{
		return table.to<address_t*>()->offset( 0x4 * index );
	}

	uint32_t get_vtable_length( address_t table )
	{
		auto length = uint32_t{};

		while ( address_t::is_safe( table.offset( 0x4 * length ) ) )
		{
			length += 1;
		}

		return length;
	}
}