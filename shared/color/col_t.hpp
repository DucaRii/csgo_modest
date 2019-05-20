#pragma once

namespace shared
{
	struct col_t
	{
		std::array<uint8_t, 4> m_color;

		col_t() = default;

		col_t( const int r, const int g, const int b ) : m_color( { 0,0,0,0 } )
		{
			set( r, g, b, 255 );
		}

		col_t( const int r, const int g, const int b, const int a ) : m_color( { 0,0,0,0 } )
		{
			set( r, g, b, a );
		}

		col_t( const float r, const float g, const float b ) : m_color( { 0,0,0,0 } )
		{
			set( static_cast< int >( r * 255 ),
				 static_cast< int >( g * 255 ),
				 static_cast< int >( b * 255 ), 255 );
		}

		col_t( const float r, const float g, const float b, const float a ) : m_color( { 0,0,0,0 } )
		{
			set( static_cast< int >( r * 255 ),
				 static_cast< int >( g * 255 ),
				 static_cast< int >( b * 255 ),
				 static_cast< int >( a * 255 ) );
		}

		col_t( const col_t& col, const int a = 255 ) : m_color( { 0,0,0,0 } )
		{
			set( col.r(), col.g(), col.b(), a );
		}

		void set( const int r, const int g, const int b, const int a )
		{
			m_color[ 0 ] = static_cast< uint8_t >( r );
			m_color[ 1 ] = static_cast< uint8_t >( g );
			m_color[ 2 ] = static_cast< uint8_t >( b );
			m_color[ 3 ] = static_cast< uint8_t >( a );
		}

		int r() const
		{
			return m_color[ 0 ];
		}

		int g() const
		{
			return m_color[ 1 ];
		}

		int b() const
		{
			return m_color[ 2 ];
		}

		int a() const
		{
			return m_color[ 3 ];
		}

		col_t& operator=( const col_t& in )
		{
			set( in.r(), in.g(), in.b(), in.a() );
			return *this;
		}

		bool operator==( const col_t& in ) const
		{
			return *const_cast< col_t* >( this ) == *const_cast< col_t* >( &in );
		}

		bool operator!=( const col_t& in ) const
		{
			return !( operator==( in ) );
		}

		/// <summary>
		/// Gets the hue of the current color
		/// </summary>
		/// <returns>Hue of color</returns>
		float hue() const
		{
			float r = m_color[ 0 ] / 255.0f;
			float g = m_color[ 1 ] / 255.0f;
			float b = m_color[ 2 ] / 255.0f;

			float mx = max( r, max( g, b ) );
			float mn = min( r, min( g, b ) );
			if ( mx == mn )
				return 0.f;

			float delta = mx - mn;

			float hue = 0.f;
			if ( mx == r )
				hue = ( g - b ) / delta;
			else if ( mx == g )
				hue = 2.f + ( b - r ) / delta;
			else
				hue = 4.f + ( r - g ) / delta;

			hue *= 60.f;
			if ( hue < 0.f )
				hue += 360.f;

			return hue / 360.f;
		}

		/// <summary>
		/// Gets the saturation of the current color
		/// </summary>
		/// <returns>Saturation of color</returns>
		float saturation() const
		{
			float r = m_color[ 0 ] / 255.0f;
			float g = m_color[ 1 ] / 255.0f;
			float b = m_color[ 2 ] / 255.0f;

			float mx = max( r, max( g, b ) );
			float mn = min( r, min( g, b ) );

			float delta = mx - mn;

			if ( mx == 0.f )
				return delta;

			return delta / mx;
		}

		/// <summary>
		/// Gets the brightness of the current color
		/// </summary>
		/// <returns>Brightness of color</returns>
		float brightness() const
		{
			float r = m_color[ 0 ] / 255.0f;
			float g = m_color[ 1 ] / 255.0f;
			float b = m_color[ 2 ] / 255.0f;

			return max( r, max( g, b ) );
		}

		/// <summary>
		/// Creates a new color object from the given arguments
		/// </summary>
		/// <param name="hue">Hue of new color</param>
		/// <param name="saturation">Saturation of new color</param>
		/// <param name="brightness">Brightness of new color</param>
		/// <returns>New color object</returns>
		static col_t from_hsb( float hue, float saturation, float brightness )
		{
			float h = hue == 1.0f ? 0 : hue * 6.0f;
			float f = h - ( int )h;
			float p = brightness * ( 1.0f - saturation );
			float q = brightness * ( 1.0f - saturation * f );
			float t = brightness * ( 1.0f - ( saturation * ( 1.0f - f ) ) );

			if ( h < 1 )
			{
				return col_t(
					( unsigned char )( brightness * 255 ),
					( unsigned char )( t * 255 ),
					( unsigned char )( p * 255 )
				);
			}
			if ( h < 2 )
			{
				return col_t(
					( unsigned char )( q * 255 ),
					( unsigned char )( brightness * 255 ),
					( unsigned char )( p * 255 )
				);
			}
			if ( h < 3 )
			{
				return col_t(
					( unsigned char )( p * 255 ),
					( unsigned char )( brightness * 255 ),
					( unsigned char )( t * 255 )
				);
			}
			if ( h < 4 )
			{
				return col_t(
					( unsigned char )( p * 255 ),
					( unsigned char )( q * 255 ),
					( unsigned char )( brightness * 255 )
				);
			}
			if ( h < 5 )
			{
				return col_t(
					( unsigned char )( t * 255 ),
					( unsigned char )( p * 255 ),
					( unsigned char )( brightness * 255 )
				);
			}
			return col_t(
				( unsigned char )( brightness * 255 ),
				( unsigned char )( p * 255 ),
				( unsigned char )( q * 255 )
			);
		}
	};
}