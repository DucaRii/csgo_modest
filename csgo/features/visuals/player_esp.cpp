#include "../../csgo.hpp"

namespace player_esp
{
	void render()
	{
		if ( !ctx::csgo.engine->IsInGame() || !ctx::csgo.engine->IsConnected() )
			return;

		game::for_every_player(
			[]( player_t * pl ) -> bool
			{
				math::vec4_t bbox{};
				if ( !pl->get_bbox( bbox ) )
					return false;

				if ( config::get<bool>( ctx::cfg.playeresp_name ) )
				{
					auto player_info = pl->get_player_info();

					render::text( render::fonts::m_main, { bbox.x + bbox.w * 0.5f, bbox.y - 7 }, { 255,255,255 }, { render::fonts::FONT_RIGHT | render::fonts::FONT_CENTER_Y }, player_info.name );
				}

				if ( config::get<bool>( ctx::cfg.playeresp_health ) )
				{
					render::text( render::fonts::m_main, { bbox.x + bbox.w * 0.5f, bbox.y - 7 }, { 255,255,255 }, { render::fonts::FONT_CENTER_Y }, fmt::format( " - [{:d}]", pl->get_health() ) );
				}

				if ( config::get<bool>( ctx::cfg.playeresp_box ) )
				{
					render::rect( { bbox.x - 1, bbox.y - 1 }, { bbox.w + 2, bbox.z + 2 }, { 10, 10, 10 } );
					render::rect( { bbox.x + 1, bbox.y + 1 }, { bbox.w - 2, bbox.z - 2 }, { 10, 10, 10 } );
					render::rect( { bbox.x, bbox.y }, { bbox.w, bbox.z }, { 255, 255, 255 } );
				}

				return false;
			}, { game::ENEMY_ONLY } );
	}
}