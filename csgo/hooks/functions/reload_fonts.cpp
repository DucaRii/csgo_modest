#include "../../csgo.hpp"

void __fastcall hook_handler_t::reload_fonts( REGISTERS )
{
	hooks::get().orig_reload_fonts( ecx, edx );

	render::undo();
	render::init();
}
