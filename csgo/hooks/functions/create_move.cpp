#include "../../csgo.hpp"

bool __fastcall hook_handler_t::create_move( REGISTERS, float flInputSampleTime, CUserCmd* cmd )
{
	if ( !cmd || !cmd->command_number )
		return hooks::get().orig_create_move( ecx, edx, flInputSampleTime, cmd );

	/// Initialize globals
	ctx::client.cmd = cmd;
	ctx::client.local = entity_t::get<player_t>( ctx::csgo.engine->GetLocalPlayer() );

	INIT_STACKFRAME();

	/// Walk up stackframe to get to previous local variables
	stack_frame.previous();

	bool* bSendPacket = stack_frame.get_var<bool*>( -0x1C );

	movement::bunnyhop();

	return false;
}