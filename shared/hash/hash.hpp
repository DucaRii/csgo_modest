#pragma once

namespace shared::hash
{
	constexpr uint64_t BASIS = 0x811c9dc5;
	constexpr uint64_t PRIME = 0x1000193;

	/// Compile-Time
	inline constexpr uint32_t get_const( const char* str, const uint32_t value = BASIS ) noexcept
	{
		/// Recursive hashing
		return ( str[ 0 ] == '\0' ) ? value :
			get_const( &str[ 1 ], ( value ^ uint32_t( str[ 0 ] ) ) * PRIME );
	}

	/// Run-Time only
	inline uint32_t get( const char* str )
	{
		uint32_t ret = BASIS;

		uint32_t length = strlen( str );
		for ( auto i = 0u; i < length; ++i )
		{
			ret ^= str[ i ];
			ret *= PRIME;
		}

		return ret;
	}
}

/// This has to be in a function kind of way since
/// it won't work with msvc else
#define CT_HASH( str ) \
       [ ]( ) { \
           constexpr uint32_t ret = shared::hash::get_const( str ); \
           return ret; \
       }( )

#define HASH( str ) shared::hash::get( str )