#pragma once

namespace shared::math
{
	enum
	{
		PITCH,
		YAW,
		ROLL
	};

	inline unsigned long& FloatBits( float& f )
	{
		return *reinterpret_cast< unsigned long* >( &f );
	}

	inline unsigned long const& FloatBits( float const& f )
	{
		return *reinterpret_cast< unsigned long const* >( &f );
	}

	inline bool IsFinite( float f )
	{
		return ( ( FloatBits( f ) & 0x7F800000 ) != 0x7F800000 );
	}

#define FLOAT32_NAN_BITS     (unsigned long)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )
}