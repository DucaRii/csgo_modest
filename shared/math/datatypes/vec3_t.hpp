#pragma once

namespace shared::math
{
	struct vec3_t
	{
		vec3_t() = default;

		vec3_t( float xyz ) : m_x( xyz ), m_y( xyz ), m_z( xyz ) {};
		vec3_t( float x, float y ) : m_x( x ), m_y( y ), m_z( 0 ) {};
		vec3_t( float x, float y, float z ) : m_x( x ), m_y( y ), m_z( z ) {};
		vec3_t( float* arr ) : m_x( arr[ PITCH ] ), m_y( arr[ YAW ] ), m_z( arr[ ROLL ] ) {};

		inline float& x()
		{
			return m_x;
		}

		inline float& y()
		{
			return m_y;
		}

		inline float& z()
		{
			return m_z;
		}

		inline float length() const
		{
			float root = 0.0f;

			float sqsr = m_x * m_x + m_y * m_y + m_z * m_z;

			__asm sqrtss xmm0, sqsr
			__asm movss root, xmm0

			return root;
		}

		inline float length_2d() const
		{
			float root = 0.0f;

			float sqst = m_x * m_x + m_y * m_y;

			__asm
			{
				sqrtss xmm0, sqst
				movss root, xmm0
			}

			return root;
		}

		inline vec3_t normalize()
		{
			vec3_t out{};
			float l = length();

			if ( l != 0 )
			{
				out.m_x = m_x / l;
				out.m_y = m_y / l;
				out.m_z = m_z / l;
			}
			else
				out.m_x = out.m_y = 0.0f; out.m_z = 1.0f;

			return out;
		}

		inline float self_dot() const
		{
			return ( m_x * m_x + m_y * m_y + m_z * m_z );
		}

		inline float dot( const vec3_t & in ) const
		{
			return ( m_x * in.m_x + m_y * in.m_y + m_z * in.m_z );
		}

		inline float dot( const float* in ) const
		{
			return ( m_x * in[ PITCH ] + m_y * in[ YAW ] + m_z * in[ ROLL ] );
		}


#pragma region assignment
		inline vec3_t& operator=( const vec3_t & in )
		{
			m_x = in.m_x;
			m_y = in.m_y;
			m_z = in.m_z;

			return *this;
		}
#pragma endregion assignment

#pragma region equality
		inline bool operator!=( const vec3_t & in )
		{
			return ( m_x != in.m_x || m_y != in.m_y || m_z != in.m_z );
		}

		inline bool operator==( const vec3_t & in )
		{
			return ( m_x == in.m_x && m_y == in.m_y && m_z == in.m_z );
		}
#pragma endregion equality

#pragma region addition
		inline vec3_t operator+( vec3_t in ) const
		{
			return vec3_t(
				m_x + in.m_x,
				m_y + in.m_y,
				m_z + in.m_z
			);
		}

		inline vec3_t operator+( float in ) const
		{
			return vec3_t(
				m_x + in,
				m_y + in,
				m_z + in
			);
		}

		inline vec3_t& operator+=( vec3_t in )
		{
			m_x += in.m_x;
			m_y += in.m_y;
			m_z += in.m_z;

			return *this;
		}

		inline vec3_t& operator+=( float in )
		{
			m_x += in;
			m_y += in;
			m_z += in;

			return *this;
		}
#pragma endregion addition

#pragma region substraction
		inline vec3_t operator-( vec3_t in ) const
		{
			return vec3_t(
				m_x - in.m_x,
				m_y - in.m_y,
				m_z - in.m_z
			);
		}

		inline vec3_t operator-( float in ) const
		{
			return vec3_t(
				m_x - in,
				m_y - in,
				m_z - in
			);
		}

		inline vec3_t& operator-=( vec3_t in )
		{
			m_x -= in.m_x;
			m_y -= in.m_y;
			m_z -= in.m_z;

			return *this;
		}

		inline vec3_t& operator-=( float in )
		{
			m_x -= in;
			m_y -= in;
			m_z -= in;

			return *this;
		}
#pragma endregion substraction

#pragma region multiplication
		inline vec3_t operator*( vec3_t in ) const
		{
			return vec3_t(
				m_x * in.m_x,
				m_y * in.m_y,
				m_z * in.m_z
			);
		}

		inline vec3_t operator*( float in ) const
		{
			return vec3_t(
				m_x * in,
				m_y * in,
				m_z * in
			);
		}

		inline vec3_t& operator*=( vec3_t in )
		{
			m_x *= in.m_x;
			m_y *= in.m_y;
			m_z *= in.m_z;

			return *this;
		}

		inline vec3_t& operator*=( float in )
		{
			m_x *= in;
			m_y *= in;
			m_z *= in;

			return *this;
		}
#pragma endregion multiplication

#pragma region division
		inline vec3_t operator/( vec3_t in ) const
		{
			return vec3_t(
				m_x / in.m_x,
				m_y / in.m_y,
				m_z / in.m_z
			);
		}

		inline vec3_t operator/( float in ) const
		{
			return vec3_t(
				m_x / in,
				m_y / in,
				m_z / in
			);
		}

		inline vec3_t& operator/=( vec3_t in )
		{
			m_x /= in.m_x;
			m_y /= in.m_y;
			m_z /= in.m_z;

			return *this;
		}

		inline vec3_t& operator/=( float in )
		{
			m_x /= in;
			m_y /= in;
			m_z /= in;

			return *this;
		}
#pragma endregion division

		float m_x, m_y, m_z;
	};
}