#pragma once

namespace shared::math
{
	struct vec4_t
	{
		vec4_t() = default;
		vec4_t( float xyzw ) : x( xyzw ), y( xyzw ), z( xyzw ), w( xyzw ) {};
		vec4_t( float x, float y ) : x( x ), y( y ), z( x ), w( y ) {};
		vec4_t( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) {};

		vec2_t get_pos() const
		{
			return vec2_t( x, y );
		}

		vec2_t get_size() const
		{
			return vec2_t( z, w );
		}

		float x, y, z, w;
	};
}