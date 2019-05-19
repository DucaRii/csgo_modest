#pragma once

namespace shared::math
{
	struct matrix3x4_t
	{
		matrix3x4_t() = default;
		matrix3x4_t(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23 )
		{
			m_matrix[ 0 ][ 0 ] = m00;
			m_matrix[ 0 ][ 1 ] = m01;
			m_matrix[ 0 ][ 2 ] = m02;
			m_matrix[ 0 ][ 3 ] = m03;
			m_matrix[ 1 ][ 0 ] = m10;
			m_matrix[ 1 ][ 1 ] = m11;
			m_matrix[ 1 ][ 2 ] = m12;
			m_matrix[ 1 ][ 3 ] = m13;
			m_matrix[ 2 ][ 0 ] = m20;
			m_matrix[ 2 ][ 1 ] = m21;
			m_matrix[ 2 ][ 2 ] = m22;
			m_matrix[ 2 ][ 3 ] = m23;
		}
		matrix3x4_t( const vec3_t& x_axis, const vec3_t& y_axis, const vec3_t& z_axis, const vec3_t& vec_origin )
		{
			init( x_axis, y_axis, z_axis, vec_origin );
		}

		void init( const vec3_t& x_axis, const vec3_t& y_axis, const vec3_t& z_axis, const vec3_t& vec_origin )
		{
			m_matrix[ 0 ][ 0 ] = x_axis.x;
			m_matrix[ 0 ][ 1 ] = y_axis.x;
			m_matrix[ 0 ][ 2 ] = z_axis.x;
			m_matrix[ 0 ][ 3 ] = vec_origin.x;
			m_matrix[ 1 ][ 0 ] = x_axis.y;
			m_matrix[ 1 ][ 1 ] = y_axis.y;
			m_matrix[ 1 ][ 2 ] = z_axis.y;
			m_matrix[ 1 ][ 3 ] = vec_origin.y;
			m_matrix[ 2 ][ 0 ] = x_axis.z;
			m_matrix[ 2 ][ 1 ] = y_axis.z;
			m_matrix[ 2 ][ 2 ] = z_axis.z;
			m_matrix[ 2 ][ 3 ] = vec_origin.z;
		}

		float* operator[]( int i )
		{
			return m_matrix[ i ];
		}

		const float* operator[]( int i ) const
		{
			return m_matrix[ i ];
		}

		float m_matrix[ 3 ][ 4 ];
	};
}