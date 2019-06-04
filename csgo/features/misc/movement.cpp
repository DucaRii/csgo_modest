#include "../../csgo.hpp"

namespace movement
{
	void bunnyhop()
	{
		if ( !config::get<bool>( ctx::cfg.movement_bhop ) )
			return;

		if ( !ctx::client.cmd )
			return;

		if ( !ctx::client.local || !ctx::client.local->is_alive() )
			return;

		/// No need to bhop there
		const auto move_type = ctx::client.local->get_move_type();
		if ( move_type == MOVETYPE_LADDER ||
			 move_type == MOVETYPE_NOCLIP ||
			 move_type == MOVETYPE_OBSERVER )
			return;

		/// Is player underwater?
		if ( ctx::client.local->get_water_level() >= 2 )
			return;

		if ( !ctx::client.local->get_flags().has_flag( FL_ONGROUND ) )
			ctx::client.cmd->buttons.remove_flag( IN_JUMP );
	}
}