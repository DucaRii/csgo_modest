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

	bool m_test_value = true;

	void frame()
	{
		if ( shared::gui::begin( "csgo_modest" ) )
		{
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
			shared::gui::toggle( "Test toggle", &m_test_value );
		}
		shared::gui::end();
	}
}