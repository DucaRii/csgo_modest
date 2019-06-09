#include "../../shared.hpp"

namespace shared::gui::controls
{
	c_tab::c_tab( std::string_view name )
		: m_skip_id( 0 ), m_style( {} ), m_max_controls( 0 )
	{
		m_name = name;

		m_name_size = gui::text_size( m_name );
	}

	void c_tab::render( math::vec2_t& pos )
	{
		m_pos = pos;

		setup_style();

		/// Get maximum controls that fit in space
		m_max_controls = static_cast< int >( gui::get_size().y / gui::get_item_size() );

		m_is_active = get_active_tab() == m_id;

		/// Tab background
		rect_filled( m_pos, m_size, m_style.m_col_inner );

		/// Get centered text position
		const auto text_pos = m_pos + m_size * 0.5f - m_name_size * 0.5f;
		text( text_pos, m_active_control_id <= 0 && m_is_active ? m_style.m_col_text_hover : m_style.m_col_text, m_name );

		/// Render line below
		rect_filled( { m_pos.x, m_pos.y + m_size.y - 2 }, { m_size.x, 2 }, m_is_active ? m_style.m_col_line_active : m_style.m_col_line );

		/// Render items only when tab is active
		if ( m_is_active )
		{
			auto control_pos = gui::get_pos() - gui::get_size() * 0.5f + math::vec2_t( 1, 0 );

			/// Now render our controls
			auto base_pos = math::vec2_t( control_pos.x, control_pos.y + m_size.y );
			auto scaled_window_size = gui::get_size().x - 2;
			for ( auto& item : m_items )
			{
				/// Check if item should even be rendered
				if ( item->get_id() <= m_skip_id ||
					 item->get_id() >= m_skip_id + m_max_controls )
					continue;

				item->set_size( math::vec2_t( scaled_window_size, static_cast< float >( get_item_size() ) ) );
				item->set_active( m_active_control_id == item->get_id() );

				item->render( base_pos );
			}
		}

		pos.x += m_size.x;
	}

	void c_tab::handle_input()
	{
		/// Don't continue input handling if tab isn't active
		if ( !m_is_active )
			return;

		/// Currently it's in tab region
		if ( m_active_control_id <= 0 )
		{
			/// Go to tab on left
			if ( input::get_mouse().m_state == input::PRESSED )
				set_active_tab( m_id - 1 );

			/// Go to tab on right
			if ( input::get_mouse().m_state_right == input::PRESSED )
				set_active_tab( m_id + 1 );

			input::get_mouse().m_state = input::IDLE;
			input::get_mouse().m_state_right = input::IDLE;
		}

		/// Dont handle anything if we dont have controls
		if ( m_items.empty() )
			return;

		bool active_id_increased = false;

		/// Handle scrolling ( item selection )
		if ( input::get_mouse().m_scroll < 0 )
		{
			m_active_control_id += 1;
			active_id_increased = true;

		}
		else if ( input::get_mouse().m_scroll > 0 )
			m_active_control_id -= 1;

		/// Clamp ID
		m_active_control_id = std::clamp( m_active_control_id, 0, static_cast< int >( m_items.size() ) );

		/// No need to handle this if tab section is selected
		if ( m_active_control_id > 0 )
		{
			/// Check if current control should be skipped ( e.g. separators )
			if ( m_items.at( m_active_control_id - 1 )->should_skip() )
			{
				/// Is control last control? Decrease
				if ( m_active_control_id == m_items.size() )
					m_active_control_id -= 1;
				else
					m_active_control_id += active_id_increased ? 1 : -1;
			}
		}

		/// Check if it needs scrolling
		if ( static_cast< int >( m_items.size() ) >= m_max_controls )
		{
			/// Calculate how many id's we have to skip
			/// +1 since control id's start at 1
			m_skip_id = m_active_control_id - m_max_controls + 1;

			m_skip_id = std::clamp( m_skip_id, 0, static_cast< int >( m_items.size() - m_max_controls + 1 ) );
		}

		/// Now lets handle the controls
		for ( const auto& item : m_items )
		{
			item->set_active( m_active_control_id == item->get_id() );
			item->handle_input();
		}
	}

	void c_tab::setup_style()
	{
		m_style.m_col_text = col_t( 220, 220, 220 );
		m_style.m_col_text_hover = col_t::palette_t::red();

		m_style.m_col_inner = col_t::palette_t::light_black();

		m_style.m_col_line_active = col_t::palette_t::red();
		m_style.m_col_line = col_t::palette_t::black( 120 );

		m_style.m_window_padding = 8;
	}

	c_control* c_tab::add( std::shared_ptr<c_control> control )
	{
		m_items.push_back( control );

		control->set_id( m_items.size() );

		return control.get();
	}
}