#include "../../shared.hpp"

namespace shared::gui::controls
{
	c_separator::c_separator( std::string_view name )
		: m_style( {} )
	{
		m_name = name;

		m_name_size = text_size( name );
	}

	void c_separator::render( math::vec2_t& pos )
	{
		m_pos = pos;

		setup_style();

		const auto separator_name_pos = math::vec2_t( m_pos.x + m_style.m_inner_padding * 3, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f );
		const auto separator_line_pos = math::vec2_t( m_pos.x + m_style.m_inner_padding * 4 + m_name_size.x, m_pos.y + m_size.y * 0.5f );

		/// Separator name
		gui::text( separator_name_pos, m_style.m_col_text, m_name );

		/// Render separator
		gui::rect( { separator_name_pos.x - m_style.m_inner_padding * 2.f, separator_line_pos.y }, { static_cast< float >( m_style.m_inner_padding ), 1.f }, m_style.m_col_separator );
		gui::rect( separator_line_pos, { m_size.x - m_name_size.x - m_style.m_inner_padding * 5.f, 1 }, m_style.m_col_separator );

		pos.y += m_size.y;
	}

	void c_separator::handle_input()
	{
		/// Ok epic
	}

	void c_separator::setup_style()
	{
		m_style.m_col_text = col_t( 220, 220, 220 );

		m_style.m_col_separator = m_style.m_col_text;

		m_style.m_inner_padding = 4;
	}
}