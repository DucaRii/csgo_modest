#include "../../csgo.hpp"

namespace player_esp
{
	bool calculate_bbox(entity_t *entity, shared::math::vec4_t &box)
	{
		shared::math::matrix3x4_t &tran_frame = entity->get_coord_frame( );

		const shared::math::vec3_t min = entity->GetCollideable( )->OBBMins( );
		const shared::math::vec3_t max = entity->GetCollideable( )->OBBMaxs( );

		shared::math::vec3_t screen_boxes[ 8 ];

		shared::math::vec3_t points[] = 
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

		for( int i = 0; i <= 7; i++ )
		{
			shared::math::vec3_t out_vec; math::vector_transform( points[ i ], tran_frame, out_vec );
			if( !game::world_to_screen( out_vec, screen_boxes[ i ] ) )
				return false;
		}

		shared::math::vec3_t box_array[] = {
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

		for( int i = 0; i <= 7; i++ ) {
			if( left > box_array[ i ].x )
				left = box_array[ i ].x;

			if( bottom < box_array[ i ].y )
				bottom = box_array[ i ].y;

			if( right < box_array[ i ].x )
				right = box_array[ i ].x;

			if( top > box_array[ i ].y )
				top = box_array[ i ].y;
		}

		box.x = left;
		box.y = top;
		box.w = right - left;
		box.z = bottom - top;

		return true;
	}
	void render()
	{
		if ( !ctx::csgo.engine->IsInGame() || !ctx::csgo.engine->IsConnected() )
			return;

		game::for_every_player(
			[]( player_t * pl ) -> bool
			{
				math::vec4_t bbox{};
				if( !calculate_bbox( pl, bbox ) )
					return false;

				if ( ctx::config.name_esp )
				{
					auto player_info = pl->get_player_info();

					render::text( render::fonts::m_main, { bbox.x + bbox.w * 0.5f, bbox.y - 7 }, { 255,255,255 }, { render::fonts::FONT_RIGHT | render::fonts::FONT_CENTER_Y }, player_info.name );
				}

				if ( ctx::config.health_esp )
				{
					render::text( render::fonts::m_main, { bbox.x + bbox.w * 0.5f, bbox.y - 7 }, { 255,255,255 }, { render::fonts::FONT_CENTER_Y }, fmt::format( " - [{:d}]", pl->get_health() ) );
				}

				if ( ctx::config.box_esp )
				{
					render::rect( { bbox.x - 1, bbox.y - 1 }, { bbox.w + 2, bbox.z + 2 }, { 10, 10, 10 } );
					render::rect( { bbox.x + 1, bbox.y + 1 }, { bbox.w - 2, bbox.z - 2 }, { 10, 10, 10 } );
					render::rect( { bbox.x, bbox.y }, { bbox.w, bbox.z }, { 255, 255, 255 } );
				}
				
				return false;
			}, { game::ENEMY_ONLY } );
	}
}