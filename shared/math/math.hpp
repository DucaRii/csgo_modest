#pragma once

#include "math_definitions.hpp"

#include "datatypes/vec2_t.hpp"
#include "datatypes/vec3_t.hpp"
#include "datatypes/angle_t.hpp"
#include "datatypes/vec4_t.hpp"
#include "datatypes/matrix3x4_t.hpp"
#include "datatypes/vert_t.h"
#include "datatypes/view_matrix_t.hpp"

namespace shared::math
{
	/// <summary>
	/// Calculates the angle from one vector to another
	/// </summary>
	/// <param name="src">The origin vector</param>
	/// <param name="dst">The destination vector</param>
	/// <results>The angle which connects the vectors</results>
	angle_t calc_angle( const vec3_t& src, const vec3_t& dst );

	/// <summary>
	/// Converts an angle to vector
	/// </summary>
	/// <param name="ang">The angle origin</param>
	/// <param name="out_forward">Forward vector</param>
	void angle_vectors( const angle_t& ang, vec3_t& out_forward );

	/// <summary>
	/// Converts an angle to vector
	/// </summary>
	/// <param name="ang">The input angle</param>
	/// <param name="out_forward">Forward vector</param>
	/// <param name="out_right">Right vector</param>
	/// <param name="out_up">Up vector</param>
	void angle_vectors( const angle_t& ang, vec3_t& out_forward, vec3_t& out_right, vec3_t& out_up );

	/// <summary>
	/// Converts a vector to an angle
	/// </summary>
	/// <param name="vec">The vector origin</param>
	/// <param name="out">Angle that is to be modified</param>
	void vector_angles( const vec3_t& vec, angle_t& out );

	/// <summary>
	/// Converts a vector and a 3x4 matrix into a new vector
	/// </summary>
	/// <param name="in_vec">Input vector</param>
	/// <param name="in_mat">Input matrix</param>
	/// <param name="out_vec">Output vector</param>
	void vector_transform( const vec3_t& in_vec, const matrix3x4_t& in_mat, vec3_t& out_vec );

}