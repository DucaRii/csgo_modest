#include "../csgo.hpp"

player_info_t entity_t::get_player_info()
{
	if ( !this )
		return {};

	player_info_t info;
	ctx::csgo.engine->GetPlayerInfo( this->EntIndex(), &info );
	return info;
}

bool entity_t::get_bbox( math::vec4_t& box )
{
	math::matrix3x4_t& tran_frame = get_coord_frame();

	const math::vec3_t min = GetCollideable()->OBBMins();
	const math::vec3_t max = GetCollideable()->OBBMaxs();

	math::vec3_t screen_boxes[ 8 ];

	math::vec3_t points[] =
	{
		{ min.x, min.y, min.z },
		{ min.x, max.y, min.z },
		{ max.x, max.y, min.z },
		{ max.x, min.y, min.z },
		{ max.x, max.y, max.z },
		{ min.x, max.y, max.z },
		{ min.x, min.y, max.z },
		{ max.x, min.y, max.z }
	};

	for ( int i = 0; i <= 7; i++ )
	{
		math::vec3_t out_vec; math::vector_transform( points[ i ], tran_frame, out_vec );
		if ( !game::world_to_screen( out_vec, screen_boxes[ i ] ) )
			return false;
	}

	math::vec3_t box_array[] = {
		screen_boxes[ 3 ], // fl
		screen_boxes[ 5 ], // br
		screen_boxes[ 0 ], // bl
		screen_boxes[ 4 ], // fr
		screen_boxes[ 2 ], // fr
		screen_boxes[ 1 ], // br
		screen_boxes[ 6 ], // bl
		screen_boxes[ 7 ] // fl
	};

	float left = screen_boxes[ 3 ].x, bottom = screen_boxes[ 3 ].y, right = screen_boxes[ 3 ].x, top = screen_boxes[ 3 ].y;

	for ( int i = 0; i <= 7; i++ )
	{
		if ( left > box_array[ i ].x )
			left = box_array[ i ].x;

		if ( bottom < box_array[ i ].y )
			bottom = box_array[ i ].y;

		if ( right < box_array[ i ].x )
			right = box_array[ i ].x;

		if ( top > box_array[ i ].y )
			top = box_array[ i ].y;
	}

	box.x = left;
	box.y = top;
	box.w = right - left;
	box.z = bottom - top;

	return true;
}

math::vec3_t player_t::get_eye_pos()
{
	auto pos = math::vec3_t{};

	weapon_shootpos( &pos );

	return pos;
}

bool player_t::is_alive()
{
	return get_lifestate() == ALIVE;
}

bool player_t::is_enemy()
{
	if ( !ctx::client.local )
		return false;

	return ctx::client.local->get_team() != this->get_team();
}
