#include "../../csgo.hpp"

void hook_handler_t::player_hurt( IGameEvent* e )
{
	if ( config::get<bool>( ctx::cfg.misc_hitmarker ) &&
		 ctx::client.local && ctx::client.local->is_alive() )
	{
		/// Check if the damage was done by us
		if ( auto attacker_id = ctx::csgo.engine->GetPlayerForUserId( e->GetInt( "attacker" ) ) == ctx::csgo.engine->GetLocalPlayer() )
			ctx::client.local->get_health_boost_time() = ctx::csgo.globals->curtime + 0.5f;
	}
}
