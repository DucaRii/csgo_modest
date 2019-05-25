#include "../../csgo.hpp"

bool __fastcall hook_handler_t::create_move( REGISTERS, float flInputSampleTime, CUserCmd* cmd )
{
	if ( !cmd || !cmd->command_number )
		return hooks::get().orig_create_move( ecx, edx, flInputSampleTime, cmd );

	return false;
}