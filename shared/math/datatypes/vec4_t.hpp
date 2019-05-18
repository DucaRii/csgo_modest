#pragma once

namespace shared::math
{
	struct vec4_t
	{
		vec4_t() = default;
		vec4_t( float xywh ) : x( xywh ), y( xywh ), w( xywh ), h( xywh ) {};
		vec4_t( float x, float y ) : x( x ), y( y ), w( x ), h( y ) {};
		vec4_t( float x, float y, float w, float h ) : x( x ), y( y ), w( w ), h( h ) {};

		vec2_t get_pos() const
		{
			return vec2_t( x, y );
		}

		vec2_t get_size() const
		{
			return vec2_t( w, h );
		}

		float x, y, w, h;
	};
}