#pragma once

namespace shared::math
{
	struct vert_t
	{
		vert_t() = default;

		vert_t( const vec2_t& pos, const vec2_t& coord = vec2_t( 0, 0 ) )
			: m_pos( pos ), m_coord( coord )
		{};

		void init( const vec2_t& pos, const vec2_t& coord = vec2_t( 0, 0 ) )
		{
			m_pos = pos;
			m_coord = coord;
		};

		vec2_t m_pos;
		vec2_t m_coord;
	};
}