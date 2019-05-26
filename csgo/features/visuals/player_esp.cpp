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
				auto pos = pl->GetRenderOrigin(),
					screen_pos = math::vec3_t{};

				/// Player position is out of screen
				if ( !game::world_to_screen( pos, screen_pos ) )
					return false;

				if ( ctx::config.name_esp )
				{
					auto player_info = pl->get_player_info();

					render::text( render::fonts::m_main, { screen_pos.x, screen_pos.y }, { 255,255,255 }, { render::fonts::FONT_RIGHT | render::fonts::FONT_CENTER_Y }, player_info.name );
				}

				if ( ctx::config.health_esp )
				{
					render::text( render::fonts::m_main, { screen_pos.x, screen_pos.y }, { 255,255,255 }, { render::fonts::FONT_CENTER_Y }, fmt::format( " - [{:d}]", pl->get_health() ) );
				}

				return false;
			}, { game::ENEMY_ONLY } );
	}
}