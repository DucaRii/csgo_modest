#pragma once

#define PITCH 0
#define YAW 1
#define ROLL 2

namespace shared::math
{
	/// <summary>
	/// Converts radians to degrees
	/// </summary>
	/// <param name="rad">Radians</param>
	/// <returns>Degrees</returns>
	inline float rad2deg( const float rad )
	{
		return static_cast<float>( rad * ( 180.f / M_PI ) );
	}

	/// <summary>
	/// Converts degrees to radians
	/// </summary>
	/// <param name="deg">Degrees</param>
	/// <returns>Radians</returns>
	inline float deg2rad( const float deg )
	{
		return static_cast< float >( deg * ( M_PI / 180.f ) );
	}

	/// <summary>
	/// Simple wrapper function to execute both sin and cos
	/// </summary>
	/// <param name="rad">The radian factor</param>
	/// <param name="sine">Sine</param>
	/// <param name="cosine">Cosine</param>
	inline void sincos( const float rad, float& sine, float& cosine )
	{
		sine = std::sin( rad );
		cosine = std::cos( rad );
	}
}