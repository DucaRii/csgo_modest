#pragma once

namespace shared::math
{
	struct angle_t
	{
		angle_t() = default;

		angle_t( float xyz ) : x( xyz ), y( xyz ), z( xyz ) {};
		angle_t( float x, float y ) : x( x ), y( y ), z( 0 ) {};
		angle_t( float x, float y, float z ) : x( x ), y( y ), z( z ) {};
		angle_t( float* arr ) : x( arr[ PITCH ] ), y( arr[ YAW ] ), z( arr[ ROLL ] ) {};

		inline float length() const
		{
			return sqrt( x * x + y * y + z * z );
		}

		inline angle_t normalize()
		{
			angle_t out{};
			float l = length();

			if ( l != 0.f )
			{
				out.x = x / l;
				out.y = y / l;
				out.z = z / l;
			}
			else
				out.x = out.y = 0.0f; out.z = 1.0f;

			return out;
		}

		inline angle_t clamp()
		{
			angle_t out{};
			
			out.x = std::clamp( x, -180.f, 180.f );
			out.y = std::clamp( y, -89.f, 89.f );
			out.z = 0.f;

			return out;
		}

#pragma region assignment
		inline angle_t& operator=( const angle_t& in )
		{
			x = in.x;
			y = in.y;
			z = in.z;

			return *this;
		}
#pragma endregion assignment

#pragma region equality
		inline bool operator!=( const angle_t& in )
		{
			return ( x != in.x || y != in.y || z != in.z );
		}

		inline bool operator==( const angle_t & in )
		{
			return ( x == in.x && y == in.y && z == in.z );
		}
#pragma endregion equality

#pragma region addition
		inline angle_t operator+( angle_t in ) const
		{
			return angle_t(
				x + in.x,
				y + in.y,
				z + in.z
			);
		}

		inline angle_t operator+( float in ) const
		{
			return angle_t(
				x + in,
				y + in,
				z + in
			);
		}

		inline angle_t& operator+=( angle_t in )
		{
			x += in.x;
			y += in.y;
			z += in.z;

			return *this;
		}

		inline angle_t& operator+=( float in )
		{
			x += in;
			y += in;
			z += in;

			return *this;
		}
#pragma endregion addition

#pragma region substraction
		inline angle_t operator-( angle_t in ) const
		{
			return angle_t(
				x - in.x,
				y - in.y,
				z - in.z
			);
		}

		inline angle_t operator-( float in ) const
		{
			return angle_t(
				x - in,
				y - in,
				z - in
			);
		}

		inline angle_t& operator-=( angle_t in )
		{
			x -= in.x;
			y -= in.y;
			z -= in.z;

			return *this;
		}

		inline angle_t& operator-=( float in )
		{
			x -= in;
			y -= in;
			z -= in;

			return *this;
		}
#pragma endregion substraction

#pragma region multiplication
		inline angle_t operator*( angle_t in ) const
		{
			return angle_t(
				x * in.x,
				y * in.y,
				z * in.z
			);
		}

		inline angle_t operator*( float in ) const
		{
			return angle_t(
				x * in,
				y * in,
				z * in
			);
		}

		inline angle_t& operator*=( angle_t in )
		{
			x *= in.x;
			y *= in.y;
			z *= in.z;

			return *this;
		}

		inline angle_t& operator*=( float in )
		{
			x *= in;
			y *= in;
			z *= in;

			return *this;
		}
#pragma endregion multiplication

#pragma region division
		inline angle_t operator/( angle_t in ) const
		{
			return angle_t(
				x / in.x,
				y / in.y,
				z / in.z
			);
		}

		inline angle_t operator/( float in ) const
		{
			return angle_t(
				x / in,
				y / in,
				z / in
			);
		}

		inline angle_t& operator/=( angle_t in )
		{
			x /= in.x;
			y /= in.y;
			z /= in.z;

			return *this;
		}

		inline angle_t& operator/=( float in )
		{
			x /= in;
			y /= in;
			z /= in;

			return *this;
		}
#pragma endregion division

		float x, y, z;
	};
}