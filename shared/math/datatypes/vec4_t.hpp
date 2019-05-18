#pragma once

namespace shared::math
{
	struct vec4_t
	{
		vec4_t() = default;
		vec4_t( float xywh ) : m_x( xywh ), m_y( xywh ), m_w( xywh ), m_h( xywh ) {};
		vec4_t( float x, float y ) : m_x( x ), m_y( y ), m_w( x ), m_h( y ) {};
		vec4_t( float x, float y, float w, float h ) : m_x( x ), m_y( y ), m_w( w ), m_h( h ) {};

		vec2_t get_pos()
		{
			return vec2_t( m_x, m_y );
		}

		vec2_t get_size()
		{
			return vec2_t( m_w, m_h );
		}

		float m_x, m_y, m_w, m_h;
	};
}