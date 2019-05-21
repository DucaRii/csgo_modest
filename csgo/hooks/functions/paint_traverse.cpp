#include "../../csgo.hpp"

void __fastcall hook_handler_t::paint_traverse( REGISTERS, int vguiPanel, bool forceRepaint, bool allowForce )
{
	hooks::get().orig_paint_traverse( ecx, edx, vguiPanel, forceRepaint, allowForce );

	static auto draw_panel = uint32_t();
	if ( !draw_panel && HASH( ctx::csgo.panel->GetName( vguiPanel ) ) == CT_HASH( "MatSystemTopPanel" ) )
		draw_panel = vguiPanel;

	if ( draw_panel != vguiPanel )
		return;

	render::init();

	render::text( render::fonts::m_main, { 100, 100 }, shared::col_t( 255, 255, 255, 255 ), {}, "Example Text" );

	render::rect_filled( { 100, 120 }, { 50, 50 }, shared::col_t( 255, 0, 0 ) );

	render::rect( { 160, 120 }, { 50, 50 }, shared::col_t( 255, 0, 0 ) );

	render::line( { 220, 120 }, { 220, 170 }, shared::col_t( 255, 0, 0 ) );

	render::circle( { 255, 145 }, 25, 128, shared::col_t( 0, 255, 0 ) );

	render::circle_filled( { 315, 145 }, 25, shared::col_t( 0, 0, 255 ) );

	shared::input::update_mouse();
}
