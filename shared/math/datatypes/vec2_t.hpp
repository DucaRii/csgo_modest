#pragma once

namespace shared::math
{
	struct vec2_t
	{
		vec2_t() = default;

		vec2_t( float xy ) : m_x( xy ), m_y( xy ) {};
		vec2_t( float x, float y ) : m_x( x ), m_y( y ) {};
		vec2_t( float x, float y, float z ) : m_x( x ), m_y( y ) {};
		vec2_t( float* arr ) : m_x( arr[ PITCH ] ), m_y( arr[ YAW ] ) {};

		inline float length() const
		{
			float root = 0.0f;

			float sqsr = m_x * m_x + m_y * m_y;

			__asm sqrtss xmm0, sqsr
			__asm movss root, xmm0

			return root;
		}

#pragma region assignment
		inline vec2_t& operator=( const vec2_t& in )
		{
			m_x = in.m_x;
			m_y = in.m_y;

			return *this;
		}
#pragma endregion assignment

#pragma region equality
		inline bool operator!=( const vec2_t& in )
		{
			return ( m_x != in.m_x || m_y != in.m_y );
		}

		inline bool operator==( const vec2_t & in )
		{
			return ( m_x == in.m_x && m_y == in.m_y );
		}
#pragma endregion equality

#pragma region addition
		inline vec2_t operator+( vec2_t in ) const
		{
			return vec2_t(
				m_x + in.m_x,
				m_y + in.m_y
			);
		}

		inline vec2_t operator+( float in ) const
		{
			return vec2_t(
				m_x + in,
				m_y + in
			);
		}

		inline vec2_t& operator+=( vec2_t in )
		{
			m_x += in.m_x;
			m_y += in.m_y;

			return *this;
		}

		inline vec2_t& operator+=( float in )
		{
			m_x += in;
			m_y += in;

			return *this;
		}
#pragma endregion addition

#pragma region substraction
		inline vec2_t operator-( vec2_t in ) const
		{
			return vec2_t(
				m_x - in.m_x,
				m_y - in.m_y
			);
		}

		inline vec2_t operator-( float in ) const
		{
			return vec2_t(
				m_x - in,
				m_y - in
			);
		}

		inline vec2_t& operator-=( vec2_t in )
		{
			m_x -= in.m_x;
			m_y -= in.m_y;

			return *this;
		}

		inline vec2_t& operator-=( float in )
		{
			m_x -= in;
			m_y -= in;

			return *this;
		}
#pragma endregion substraction

#pragma region multiplication
		inline vec2_t operator*( vec2_t in ) const
		{
			return vec2_t(
				m_x * in.m_x,
				m_y * in.m_y
			);
		}

		inline vec2_t operator*( float in ) const
		{
			return vec2_t(
				m_x * in,
				m_y * in
			);
		}

		inline vec2_t& operator*=( vec2_t in )
		{
			m_x *= in.m_x;
			m_y *= in.m_y;

			return *this;
		}

		inline vec2_t& operator*=( float in )
		{
			m_x *= in;
			m_y *= in;

			return *this;
		}
#pragma endregion multiplication

#pragma region division
		inline vec2_t operator/( vec2_t in ) const
		{
			return vec2_t(
				m_x / in.m_x,
				m_y / in.m_y
			);
		}

		inline vec2_t operator/( float in ) const
		{
			return vec2_t(
				m_x / in,
				m_y / in
			);
		}

		inline vec2_t& operator/=( vec2_t in )
		{
			m_x /= in.m_x;
			m_y /= in.m_y;

			return *this;
		}

		inline vec2_t& operator/=( float in )
		{
			m_x /= in;
			m_y /= in;

			return *this;
		}
#pragma endregion division

		float m_x, m_y;
	};
}