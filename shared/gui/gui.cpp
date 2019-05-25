#include "../shared.hpp"

namespace shared::gui
{
	render_functions_t m_functions = {};

	math::vec2_t m_pos = { 64.0f, 24.0f };

	bool m_open = false;
	int m_element_idx = 0;

	std::vector<gui_element_t> m_elements;

	render_functions_t& get_functions()
	{
		return m_functions;
	}

	bool begin( std::string_view title )
	{
		m_elements.clear();

		if ( m_open )
		{
			math::vec2_t title_size = get_functions().m_text_size( title );

			get_functions().m_text( m_pos, col_t( 255, 180, 50 ), title );
		}

		return m_open;
	}

	void end()
	{
		int elem_idx = 0;
		math::vec2_t draw_pos = m_pos + math::vec2_t( 8.0f, 24.0f );

		for ( const gui_element_t& elem : m_elements )
		{
			if ( elem.m_type == UNKNOWN )
				continue;

			bool element_active = elem_idx++ == m_element_idx;

			math::vec2_t label_size = get_functions().m_text_size( elem.m_label );
			col_t text_color = element_active ? col_t( 255, 220, 50 ) : col_t( 255, 255, 255 );

			get_functions().m_text( draw_pos, text_color, elem.m_label );

			switch ( elem.m_type )
			{
				case TOGGLE:
					get_functions().m_text( draw_pos + math::vec2_t( label_size.x + 8.0f, 0.0f ), text_color,
											*elem.m_toggle.m_value_ptr ? elem.m_toggle.m_enabled_str : elem.m_toggle.m_disabled_str );

					break;

				case SLIDER:
					get_functions().m_text( draw_pos + math::vec2_t( label_size.x + 8.0f, 0.0f ), text_color,
											fmt::format( elem.m_slider.m_display_format, *elem.m_slider.m_value_ptr ) );

					break;

				case SELECT:
					get_functions().m_text( draw_pos + math::vec2_t( label_size.x + 8.0f, 0.0f ), text_color,
											fmt::format( elem.m_select.m_display_format, elem.m_select.m_options.at( *elem.m_select.m_value_ptr ) ) );

					break;

			}

			draw_pos += math::vec2_t( 0.0f, label_size.y + 4.0f );
		}
	}

	void process_input()
	{
		if ( !m_elements.empty() )
		{
			if ( input::get_mouse().m_scroll != 0 )
				m_element_idx += input::get_mouse().m_scroll;

			if ( m_element_idx < 0 )
				m_element_idx = m_elements.size() - 1;
			else if ( m_element_idx > static_cast< int >( m_elements.size() - 1 ) )
				m_element_idx = static_cast< int >( m_elements.size() - 1 );

			gui_element_t& active = m_elements.at( m_element_idx );

			if ( active.m_type == UNKNOWN )
				return;

			switch ( active.m_type )
			{
				case TOGGLE:
					if ( input::get_mouse().m_state == input::PRESSED || input::get_mouse().m_state_right == input::PRESSED )
						( *active.m_slider.m_value_ptr ) = !( *active.m_slider.m_value_ptr );

					break;

				case SLIDER:
					if ( input::get_mouse().m_state == input::PRESSED )
						( *active.m_slider.m_value_ptr )--;
					else if ( input::get_mouse().m_state_right == input::PRESSED )
						( *active.m_slider.m_value_ptr )++;

					*active.m_slider.m_value_ptr = std::clamp( *active.m_slider.m_value_ptr, active.m_slider.m_min_value, active.m_slider.m_max_value );

					break;

				case SELECT:
					if ( input::get_mouse().m_state == input::PRESSED )
						( *active.m_select.m_value_ptr )--;
					else if ( input::get_mouse().m_state_right == input::PRESSED )
						( *active.m_select.m_value_ptr )++;

					if ( *active.m_select.m_value_ptr < 0 )
						( *active.m_select.m_value_ptr ) = static_cast< int >( active.m_select.m_options.size() - 1 );
					else if ( *active.m_select.m_value_ptr > static_cast< int >( active.m_select.m_options.size() - 1 ) )
						( *active.m_select.m_value_ptr ) = 0;

					break;

			}
		}
	}

	void toggle( std::string_view label, bool* value_ptr, std::string_view enabled_str, std::string_view disabled_str )
	{
		gui_element_t elem;

		elem.m_type = TOGGLE;
		elem.m_label = label;
		elem.m_toggle.m_value_ptr = value_ptr;
		elem.m_toggle.m_enabled_str = enabled_str;
		elem.m_toggle.m_disabled_str = disabled_str;

		m_elements.push_back( elem );
	}

	void slider( std::string_view label, float* value_ptr, float min_value, float max_value, std::string_view display_format )
	{
		gui_element_t elem;

		elem.m_type = SLIDER;
		elem.m_label = label;
		elem.m_slider.m_value_ptr = value_ptr;
		elem.m_slider.m_min_value = min_value;
		elem.m_slider.m_max_value = max_value;
		elem.m_slider.m_display_format = display_format;

		m_elements.push_back( elem );
	}

	void select( std::string_view label, int* value_ptr, const std::vector<std::string_view>& options, std::string_view display_format )
	{
		gui_element_t elem;

		elem.m_type = SELECT;
		elem.m_label = label;
		elem.m_select.m_value_ptr = value_ptr;
		elem.m_select.m_display_format = display_format;
		elem.m_select.m_options = options;

		m_elements.push_back( elem );
	}

	void toggle()
	{
		if ( input::get_key_info( VK_INSERT ).m_state == input::PRESSED )
		{
			m_open = !m_open;
		}
	}

	bool is_open()
	{
		return m_open;
	}
}