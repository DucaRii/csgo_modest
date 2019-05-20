#pragma once 

/// Modified version of this: https://github.com/nicolausYes/easing-functions

namespace shared::easing
{
	/// <summary>
	/// Scales your number based on the inSine effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_sine( const double t )
	{
		return sin( 1.5707963 * t );
	}

	/// <summary>
	/// Scales your number based on the outSine effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_sine( double t )
	{
		return 1 + sin( 1.5707963 * ( --t ) );
	}

	/// <summary>
	/// Scales your number based on the inOutSine effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_sine( const double t )
	{
		return 0.5* ( 1 + sin( 3.1415926 * ( t - 0.5 ) ) );
	}

	/// <summary>
	/// Scales your number based on the inQuad effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_quad( const double t )
	{
		return t * t;
	}

	/// <summary>
	/// Scales your number based on the outQuad effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_quad( const double t )
	{
		return t * ( 2 - t );
	}

	/// <summary>
	/// Scales your number based on the inOutQuad effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_quad( const double t )
	{
		return t < 0.5 ? 2 * t * t : t * ( 4 - 2 * t ) - 1;
	}

	/// <summary>
	/// Scales your number based on the inCubic effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_cubic( const double t )
	{
		return t * t* t;
	}

	/// <summary>
	/// Scales your number based on the outCubic effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_cubic( double t )
	{
		return 1 + ( --t ) * t * t;
	}

	/// <summary>
	/// Scales your number based on the inOutCubic effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_cubic( double t )
	{
		return t < 0.5 ? 4 * t * t * t : 1 + ( --t ) * ( 2 * ( --t ) ) * ( 2 * t );
	}

	/// <summary>
	/// Scales your number based on the inQuart effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_quart( double t )
	{
		t *= t;
		return t * t;
	}

	/// <summary>
	/// Scales your number based on the outQuart effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_quart( double t )
	{
		t = ( --t ) * t;
		return 1 - t * t;
	}

	/// <summary>
	/// Scales your number based on the inOutQuart effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_quart( double t )
	{
		if ( t < 0.5 )
		{
			t *= t;
			return 8 * t* t;
		}
		else
		{
			t = ( --t ) * t;
			return 1 - 8 * t * t;
		}
	}

	/// <summary>
	/// Scales your number based on the inQuint effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_quint( const double t )
	{
		const double t2 = t * t;
		return t * t2* t2;
	}

	/// <summary>
	/// Scales your number based on the outQuint effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_quint( double t )
	{
		const double t2 = ( --t ) * t;
		return 1 + t * t2 * t2;
	}

	/// <summary>
	/// Scales your number based on the inOutQuint effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_quint( double t )
	{
		double t2;
		if ( t < 0.5 )
		{
			t2 = t * t;
			return 16 * t* t2* t2;
		}
		else
		{
			t2 = ( --t ) * t;
			return 1 + 16 * t * t2 * t2;
		}
	}

	/// <summary>
	/// Scales your number based on the inExpo effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_expo( const double t )
	{
		return ( pow( 2, 8 * t ) - 1 ) / 255;
	}

	/// <summary>
	/// Scales your number based on the outExpo effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_expo( const double t )
	{
		return 1 - pow( 2, -8 * t );
	}

	/// <summary>
	/// Scales your number based on the inOutExpo effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_expo( const double t )
	{
		if ( t < 0.5 )
		{
			return ( pow( 2, 16 * t ) - 1 ) / 510;
		}
		else
		{
			return 1 - 0.5 * pow( 2, -16 * ( t - 0.5 ) );
		}
	}

	/// <summary>
	/// Scales your number based on the inCirc effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_circ( const double t )
	{
		return 1 - sqrt( 1 - t );
	}

	/// <summary>
	/// Scales your number based on the outCirc effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_circ( const double t )
	{
		return sqrt( t );
	}

	/// <summary>
	/// Scales your number based on the inOutCirc effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_circ( const double t )
	{
		if ( t < 0.5 )
		{
			return ( 1 - sqrt( 1 - 2 * t ) ) * 0.5;
		}
		else
		{
			return ( 1 + sqrt( 2 * t - 1 ) ) * 0.5;
		}
	}

	/// <summary>
	/// Scales your number based on the inBack effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_back( const double t )
	{
		return t * t* ( 2.70158 * t - 1.70158 );
	}

	/// <summary>
	/// Scales your number based on the outBack effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_back( double t )
	{
		return 1 + ( --t ) * t * ( 2.70158 * t + 1.70158 );
	}

	/// <summary>
	/// Scales your number based on the inOutBack effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_back( double t )
	{
		if ( t < 0.5 )
		{
			return t * t* ( 7 * t - 2.5 ) * 2;
		}
		else
		{
			return 1 + ( --t ) * t * 2 * ( 7 * t + 2.5 );
		}
	}

	/// <summary>
	/// Scales your number based on the inElastic effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_elastic( const double t )
	{
		const double t2 = t * t;
		return t2 * t2* sin( t * M_PI * 4.5 );
	}

	/// <summary>
	/// Scales your number based on the outElastic effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_elastic( const double t )
	{
		const double t2 = ( t - 1 ) * ( t - 1 );
		return 1 - t2 * t2 * cos( t * M_PI * 4.5 );
	}

	/// <summary>
	/// Scales your number based on the inOutElastic effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_elastic( const double t )
	{
		double t2;
		if ( t < 0.45 )
		{
			t2 = t * t;
			return 8 * t2* t2* sin( t * M_PI * 9 );
		}
		else if ( t < 0.55 )
		{
			return 0.5 + 0.75 * sin( t * M_PI * 4 );
		}
		else
		{
			t2 = ( t - 1 ) * ( t - 1 );
			return 1 - 8 * t2 * t2 * sin( t * M_PI * 9 );
		}
	}

	/// <summary>
	/// Scales your number based on the inBounce effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_bounce( const double t )
	{
		return pow( 2, 6 * ( t - 1 ) ) * abs( sin( t * M_PI * 3.5 ) );
	}

	/// <summary>
	/// Scales your number based on the outBounce effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double out_bounce( const double t )
	{
		return 1 - pow( 2, -6 * t ) * abs( cos( t * M_PI * 3.5 ) );
	}

	/// <summary>
	/// Scales your number based on the inOutBounce effect
	/// </summary>
	/// <param name="t">Input factor (0..1)</param>
	/// <returns>Scaled value</returns>
	inline double in_out_bounce( const double t )
	{
		if ( t < 0.5 )
		{
			return 8 * pow( 2, 8 * ( t - 1 ) ) * abs( sin( t * M_PI * 7 ) );
		}
		else
		{
			return 1 - 8 * pow( 2, -8 * t ) * abs( sin( t * M_PI * 7 ) );
		}
	}
}