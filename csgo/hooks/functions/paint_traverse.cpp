#include "../../csgo.hpp"

void __fastcall hook_handler_t::paint_traverse( REGISTERS, int vguiPanel, bool forceRepaint, bool allowForce )
{
	hooks::get().orig_paint_traverse( ecx, edx, vguiPanel, forceRepaint, allowForce );

	static auto draw_panel = uint32_t();
	if ( !draw_panel && HASH( ctx::csgo.panel()->GetName( vguiPanel ) ) == CT_HASH( "MatSystemTopPanel" ) )
		draw_panel = vguiPanel;

	if ( draw_panel != vguiPanel )
		return;

	render::init( ctx::csgo.surface() );

	auto size = render::text_size( render::fonts::m_main, "HEEEY565678565678" );

	ctx::csgo.surface()->DrawSetColor( 255, 0, 255, 255 );
	ctx::csgo.surface()->DrawFilledRect( 200, 200, 200 + size.x, 200 + size.y );

	ctx::csgo.surface()->DrawColoredText( render::fonts::m_main, 200, 200, 255, 0, 0, 255, "HEEEY565678565678" );

	shared::input::update_mouse();
}
