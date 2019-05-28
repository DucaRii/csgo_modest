#pragma once

#include "../math_definitions.hpp"

namespace shared::math
{
	struct vec2_t
	{
		vec2_t() = default;

		vec2_t( float xy ) : x( xy ), y( xy ) {};
		vec2_t( float x, float y ) : x( x ), y( y ) {};
		vec2_t( float x, float y, float z ) : x( x ), y( y ) {};
		vec2_t( float* arr ) : x( arr[ PITCH ] ), y( arr[ YAW ] ) {};

		inline float length() const
		{
			return sqrt( x * x + y * y );
		}

		inline bool is_zero() const
		{
			return x == 0 && y == 0;
		}

#pragma region assignment
		inline vec2_t& operator=( const vec2_t& in )
		{
			x = in.x;
			y = in.y;

			return *this;
		}
#pragma endregion assignment

#pragma region equality
		inline bool operator!=( const vec2_t& in )
		{
			return ( x != in.x || y != in.y );
		}

		inline bool operator==( const vec2_t & in )
		{
			return ( x == in.x && y == in.y );
		}
#pragma endregion equality

#pragma region addition
		inline vec2_t operator+( vec2_t in ) const
		{
			return vec2_t(
				x + in.x,
				y + in.y
			);
		}

		inline vec2_t operator+( float in ) const
		{
			return vec2_t(
				x + in,
				y + in
			);
		}

		inline vec2_t& operator+=( vec2_t in )
		{
			x += in.x;
			y += in.y;

			return *this;
		}

		inline vec2_t& operator+=( float in )
		{
			x += in;
			y += in;

			return *this;
		}
#pragma endregion addition

#pragma region substraction
		inline vec2_t operator-( vec2_t in ) const
		{
			return vec2_t(
				x - in.x,
				y - in.y
			);
		}

		inline vec2_t operator-( float in ) const
		{
			return vec2_t(
				x - in,
				y - in
			);
		}

		inline vec2_t& operator-=( vec2_t in )
		{
			x -= in.x;
			y -= in.y;

			return *this;
		}

		inline vec2_t& operator-=( float in )
		{
			x -= in;
			y -= in;

			return *this;
		}
#pragma endregion substraction

#pragma region multiplication
		inline vec2_t operator*( vec2_t in ) const
		{
			return vec2_t(
				x * in.x,
				y * in.y
			);
		}

		inline vec2_t operator*( float in ) const
		{
			return vec2_t(
				x * in,
				y * in
			);
		}

		inline vec2_t& operator*=( vec2_t in )
		{
			x *= in.x;
			y *= in.y;

			return *this;
		}

		inline vec2_t& operator*=( float in )
		{
			x *= in;
			y *= in;

			return *this;
		}
#pragma endregion multiplication

#pragma region division
		inline vec2_t operator/( vec2_t in ) const
		{
			return vec2_t(
				x / in.x,
				y / in.y
			);
		}

		inline vec2_t operator/( float in ) const
		{
			return vec2_t(
				x / in,
				y / in
			);
		}

		inline vec2_t& operator/=( vec2_t in )
		{
			x /= in.x;
			y /= in.y;

			return *this;
		}

		inline vec2_t& operator/=( float in )
		{
			x /= in;
			y /= in;

			return *this;
		}
#pragma endregion division

		float x, y;
	};
}