#include "../../csgo.hpp"

void __fastcall hook_handler_t::paint_traverse( uintptr_t ecx, uintptr_t edx, int vguiPanel, bool forceRepaint, bool allowForce )
{
	hooks::get().orig_paint_traverse( ecx, edx, vguiPanel, forceRepaint, allowForce );
}
