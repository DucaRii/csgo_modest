#include "../../csgo.hpp"

void __fastcall hook_handler_t::paint( REGISTERS, int mode )
{
	hooks::get().orig_paint( ecx, edx, mode );

	if ( mode & PAINT_UIPANELS )
	{
		ctx::csgo.surface->StartDrawing();
		{
			if ( input::get_key_info( VK_XBUTTON1 ).is_pressed() )
				config::save();

			if ( input::get_key_info( VK_XBUTTON2 ).is_pressed() )
				config::load();

			render::init();

			/// Example usage of render functions
			/*render::text( render::fonts::m_main, { 100, 100 }, col_t( 255, 255, 255, 255 ), {}, "Example Text" );

			render::rect_filled( { 100, 120 }, { 50, 50 }, col_t( 255, 0, 0 ) );

			render::rect( { 160, 120 }, { 50, 50 }, col_t( 255, 0, 0 ) );

			render::line( { 220, 120 }, { 220, 170 }, col_t( 255, 0, 0 ) );

			render::circle( { 255, 145 }, 25, 128, col_t( 0, 255, 0 ) );

			render::circle_filled( { 315, 145 }, 25, 128, col_t( 0, 0, 255 ) );

			render::triangle_filled( { 340, 170 }, { 365, 120 }, { 390, 170 }, col_t( 0, 255, 255 ) );*/

			player_esp::render();

			menu::render();

			input::update_mouse();
		}
		ctx::csgo.surface->FinishDrawing();
	}
}
