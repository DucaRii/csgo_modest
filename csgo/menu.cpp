#include "csgo.hpp"

namespace menu
{
	void init()
	{
		/// Set up render functions
		shared::gui::get_functions().m_fill_rect = render::rect_filled;
		shared::gui::get_functions().m_rect = render::rect;
		shared::gui::get_functions().m_line = render::line;
		shared::gui::get_functions().m_text = [ & ]( const shared::math::vec2_t& pos, const shared::col_t& color, std::string_view text )
		{
			render::text( render::fonts::m_menu, pos, color, 0, text );
		};
		shared::gui::get_functions().m_text_size = [ & ]( std::string_view text ) -> shared::math::vec2_t
		{
			return render::text_size( render::fonts::m_menu, text );
		};
	}

	bool m_test_toggle = true;
	float m_test_slider = 25.0f;
	int m_test_select = 0;

	void frame()
	{
		if ( shared::gui::begin( "csgo_modest" ) )
		{
			shared::gui::toggle( "Test toggle", &m_test_toggle );
			shared::gui::slider( "Test slider", &m_test_slider, 0.0f, 100.0f );
			shared::gui::select( "Test select", &m_test_select, { "Option 1", "Option 2", "Option 3" }, "Selected: {}" );
		}
		shared::gui::end();
	}
}