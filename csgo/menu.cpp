#include "csgo.hpp"

namespace menu
{
	void init()
	{
		/// Set up render functions
		gui::get_functions().m_fill_rect = render::rect_filled;
		gui::get_functions().m_rect = render::rect;
		gui::get_functions().m_line = render::line;
		gui::get_functions().m_text = [ & ]( const math::vec2_t& pos, const col_t& color, std::string_view text )
		{
			render::text( render::fonts::m_menu, pos, color, 0, text );
		};
		gui::get_functions().m_text_size = [ & ]( std::string_view text ) -> math::vec2_t
		{
			return render::text_size( render::fonts::m_menu, text );
		};
	}

	bool m_test_toggle = true;
	float m_test_slider = 25.0f;
	int m_test_select = 0;

	void render()
	{
		if ( gui::begin( "csgo_modest" ) )
		{
			gui::toggle( "Bunnyhop", &ctx::config.bhop );
			gui::toggle( "Name ESP", &ctx::config.name_esp );
			gui::toggle( "Health ESP", &ctx::config.health_esp );

			gui::toggle( "Test toggle", &m_test_toggle );
			gui::slider( "Test slider", &m_test_slider, 0.0f, 100.0f );
			gui::select( "Test select", &m_test_select, { "Option 1", "Option 2", "Option 3" }, "Selected: {}" );
		}
		gui::end();
	}
}