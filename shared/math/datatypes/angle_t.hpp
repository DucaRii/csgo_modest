#pragma once

namespace shared::math
{
	struct angle_t
	{
		angle_t() = default;

		angle_t( float xyz ) : m_x( xyz ), m_y( xyz ), m_z( xyz ) {};
		angle_t( float x, float y ) : m_x( x ), m_y( y ), m_z( 0 ) {};
		angle_t( float x, float y, float z ) : m_x( x ), m_y( y ), m_z( z ) {};
		angle_t( float* arr ) : m_x( arr[ PITCH ] ), m_y( arr[ YAW ] ), m_z( arr[ ROLL ] ) {};

		inline float length() const
		{
			float root = 0.0f;

			float sqsr = m_x * m_x + m_y * m_y + m_z * m_z;

			__asm sqrtss xmm0, sqsr
			__asm movss root, xmm0

			return root;
		}

		inline angle_t normalize()
		{
			angle_t out{};
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

#pragma region assignment
		inline angle_t& operator=( const angle_t& in )
		{
			m_x = in.m_x;
			m_y = in.m_y;
			m_z = in.m_z;

			return *this;
		}
#pragma endregion assignment

#pragma region equality
		inline bool operator!=( const angle_t& in )
		{
			return ( m_x != in.m_x || m_y != in.m_y || m_z != in.m_z );
		}

		inline bool operator==( const angle_t & in )
		{
			return ( m_x == in.m_x && m_y == in.m_y && m_z == in.m_z );
		}
#pragma endregion equality

#pragma region addition
		inline angle_t operator+( angle_t in ) const
		{
			return angle_t(
				m_x + in.m_x,
				m_y + in.m_y,
				m_z + in.m_z
			);
		}

		inline angle_t operator+( float in ) const
		{
			return angle_t(
				m_x + in,
				m_y + in,
				m_z + in
			);
		}

		inline angle_t& operator+=( angle_t in )
		{
			m_x += in.m_x;
			m_y += in.m_y;
			m_z += in.m_z;

			return *this;
		}

		inline angle_t& operator+=( float in )
		{
			m_x += in;
			m_y += in;
			m_z += in;

			return *this;
		}
#pragma endregion addition

#pragma region substraction
		inline angle_t operator-( angle_t in ) const
		{
			return angle_t(
				m_x - in.m_x,
				m_y - in.m_y,
				m_z - in.m_z
			);
		}

		inline angle_t operator-( float in ) const
		{
			return angle_t(
				m_x - in,
				m_y - in,
				m_z - in
			);
		}

		inline angle_t& operator-=( angle_t in )
		{
			m_x -= in.m_x;
			m_y -= in.m_y;
			m_z -= in.m_z;

			return *this;
		}

		inline angle_t& operator-=( float in )
		{
			m_x -= in;
			m_y -= in;
			m_z -= in;

			return *this;
		}
#pragma endregion substraction

#pragma region multiplication
		inline angle_t operator*( angle_t in ) const
		{
			return angle_t(
				m_x * in.m_x,
				m_y * in.m_y,
				m_z * in.m_z
			);
		}

		inline angle_t operator*( float in ) const
		{
			return angle_t(
				m_x * in,
				m_y * in,
				m_z * in
			);
		}

		inline angle_t& operator*=( angle_t in )
		{
			m_x *= in.m_x;
			m_y *= in.m_y;
			m_z *= in.m_z;

			return *this;
		}

		inline angle_t& operator*=( float in )
		{
			m_x *= in;
			m_y *= in;
			m_z *= in;

			return *this;
		}
#pragma endregion multiplication

#pragma region division
		inline angle_t operator/( angle_t in ) const
		{
			return angle_t(
				m_x / in.m_x,
				m_y / in.m_y,
				m_z / in.m_z
			);
		}

		inline angle_t operator/( float in ) const
		{
			return angle_t(
				m_x / in,
				m_y / in,
				m_z / in
			);
		}

		inline angle_t& operator/=( angle_t in )
		{
			m_x /= in.m_x;
			m_y /= in.m_y;
			m_z /= in.m_z;

			return *this;
		}

		inline angle_t& operator/=( float in )
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