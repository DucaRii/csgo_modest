#include "../../shared.hpp"

namespace shared::gui::controls
{
	c_checkbox::c_checkbox( std::string_view name, config::item_t* var )
		: m_style( {} )
	{
		m_name = name;

		m_name_size = text_size( name );

		m_var = var;
	}

	void c_checkbox::render( math::vec2_t& pos )
	{
		m_pos = pos;

		setup_style();

		const auto control_name_pos = math::vec2_t( m_pos.x + m_style.m_inner_padding, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f );

		/// Control name
		gui::text( control_name_pos, m_is_active ? m_style.m_col_text_hover : m_style.m_col_text, m_name );

		/// Render checkbox
		render_checkbox();

		pos.y += m_size.y;
	}

	void c_checkbox::handle_input()
	{
		if ( !m_is_active )
			return;

		/// Checkbox toggle
		if ( input::get_mouse().m_state == input::PRESSED
			 || input::get_mouse().m_state_right == input::PRESSED )
		{
			/// Last action has to be atleast 0.25 seconds in the past
			if ( get_curtime() - m_last_action > 0.25f )
			{
				push_action( get_curtime() );

				m_var->get<bool>() = !m_var->get<bool>();
			}
		}
	}

	void c_checkbox::setup_style()
	{
		m_style.m_col_text = col_t( 220, 220, 220 );
		m_style.m_col_text_hover = col_t::palette_t::red();

		m_style.m_col_checkbox = col_t::palette_t::grey();
		m_style.m_col_checkbox_active = col_t::palette_t::red();
		m_style.m_col_checkbox_inner = col_t::palette_t::black( 100 );
		m_style.m_col_checkbox_outline = col_t::palette_t::light_black();

		m_style.m_inner_padding = 4;

		m_style.m_checkbox_width = 22;
	}

	void c_checkbox::render_checkbox()
	{
		const auto checkbox_pos = math::vec2_t( m_pos.x + m_style.m_inner_padding, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f + 1 );
		const auto checkbox_size = math::vec2_t( m_size.x - m_style.m_inner_padding * 2, m_name_size.y - 4 );

		/// Checkbox inner
		gui::rect_filled( math::vec2_t( checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width, checkbox_pos.y ), math::vec2_t( static_cast< float >( m_style.m_checkbox_width ), checkbox_size.y ), m_style.m_col_checkbox_inner );

		/// Clip so it doesnt cross boundaries
		gui::clip( math::vec2_t( checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width + 1, checkbox_pos.y ), math::vec2_t( m_style.m_checkbox_width - 2.f, checkbox_size.y ) );

		/// Actual checkbox
		const auto dot_factor = static_cast< float >( easing::in_out_sine( std::clamp( get_curtime() - m_last_action, 0.f, .25f ) * 4.f ) );
		const auto dot_offset = dot_factor * m_style.m_checkbox_width * 0.5f;
		gui::rect_filled( math::vec2_t( m_var->get<bool>() ? checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width + dot_offset
										: checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width * 0.5f - dot_offset, checkbox_pos.y ),
						  math::vec2_t( m_style.m_checkbox_width * 0.5f, checkbox_size.y ), m_style.m_col_checkbox );

		gui::rect_filled( math::vec2_t( m_var->get<bool>() ? checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width + dot_offset
										: checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width * 0.5f - dot_offset, checkbox_pos.y ),
						  math::vec2_t( m_style.m_checkbox_width * 0.5f, checkbox_size.y ), col_t( m_style.m_col_checkbox_active, static_cast< int >( ( m_var->get<bool>() ? dot_factor : 1.f - dot_factor ) * 255.f ) ) );

		/// Reset clip
		gui::reset_clip();

		/// Outline
		gui::rect( math::vec2_t( checkbox_pos.x + checkbox_size.x - m_style.m_checkbox_width, checkbox_pos.y ), math::vec2_t( static_cast< float >( m_style.m_checkbox_width ), checkbox_size.y ), m_style.m_col_checkbox_outline );
	}
}