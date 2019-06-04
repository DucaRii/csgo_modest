#include "../../shared.hpp"

namespace shared::gui::controls
{
	c_combo::c_combo( std::string_view name, config::item_t* var, std::vector<std::string_view> items )
		: m_style( {} )
	{
		m_name = name;

		m_name_size = text_size( name );

		m_items = items;

		/// Find largest item size and set combobox width to it
		auto largest_width = 0;
		for ( const auto& item : m_items )
		{
			auto width = static_cast< int >( gui::text_size( item ).x );
			if ( width > largest_width )
				largest_width = width;

			m_item_widths.push_back( width );
		}

		m_style.m_combobox_width = largest_width;

		m_var = var;
	}

	void c_combo::render( math::vec2_t& pos )
	{
		m_pos = pos;

		setup_style();

		const auto control_name_pos = math::vec2_t( m_pos.x + m_style.m_inner_padding, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f );

		/// Control name
		gui::text( control_name_pos, m_is_active ? m_style.m_col_text_hover : m_style.m_col_text, m_name );

		/// Render checkbox
		render_combobox();

		/// Render item preview
		render_preview();

		pos.y += m_size.y;
	}

	void c_combo::handle_input()
	{
		if ( !m_is_active )
			return;

		/// Go to item on left
		if ( input::get_mouse().m_state == input::PRESSED )
			m_var->get<int>()--;
		/// Go to item on right
		else if ( input::get_mouse().m_state_right == input::PRESSED )
			m_var->get<int>()++;

		/// "Clamp" value
		if ( m_var->get<int>() < 0 )
			m_var->get<int>() = m_items.size() - 1;
		else if ( m_var->get<int>() > static_cast< int >( m_items.size() - 1 ) )
			m_var->get<int>() = 0;
	}

	void c_combo::setup_style()
	{
		m_style.m_col_text = col_t( 220, 220, 220 );
		m_style.m_col_text_hover = col_t::palette_t::red();

		m_style.m_col_combobox_inner = col_t::palette_t::black( 100 );
		m_style.m_col_combobox_outline = col_t::palette_t::light_black();

		m_style.m_col_combobox_popup = col_t::palette_t::dark_grey();

		m_style.m_inner_padding = 4;
	}

	void c_combo::render_combobox()
	{
		const auto combobox_pos = math::vec2_t( m_pos.x + m_size.x - m_style.m_inner_padding * 3.f - m_style.m_combobox_width, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f );
		const auto combobox_size = math::vec2_t( m_style.m_combobox_width + m_style.m_inner_padding * 2.f, m_name_size.y );

		/// Combobox inner
		gui::rect_filled( combobox_pos, combobox_size, m_style.m_col_combobox_inner );

		/// Current selected item
		gui::text( { combobox_pos.x + combobox_size.x * 0.5f - m_item_widths.at( m_var->get<int>() ) * 0.5f, combobox_pos.y }, m_style.m_col_text, m_items.at( m_var->get<int>() ) );

		/// Outline
		gui::rect( combobox_pos, combobox_size, m_style.m_col_combobox_outline );
	}

	void c_combo::render_preview()
	{
		/// Don't render preview if its not selected
		if ( !m_is_active )
			return;

		const auto pos = math::vec2_t( m_pos.x + m_size.x + m_style.m_inner_padding * 3.f, m_pos.y - ( m_var->get<int>() ) * m_name_size.y );
		const auto size = math::vec2_t( m_style.m_combobox_width + m_style.m_inner_padding * 2.f, m_items.size() * m_name_size.y );

		/// Draw background
		gui::rect_filled( pos, size, m_style.m_col_combobox_popup );

		/// Outline
		gui::rect( pos, size, m_style.m_col_combobox_outline );

		/// Render items
		for ( auto i = 0u; i < m_items.size(); i++ )
		{
			gui::text( { pos.x + size.x * 0.5f - m_item_widths.at( i ) * 0.5f, pos.y + i * m_name_size.y }, i == m_var->get<int>() ? m_style.m_col_text_hover : m_style.m_col_text, m_items.at( i ) );
		}
	}
}