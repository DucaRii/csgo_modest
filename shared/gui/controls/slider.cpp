#include "../../shared.hpp"

namespace shared::gui::controls
{
	c_slider::c_slider( std::string_view name, config::item_t* var, float min, float max, float step )
		: m_style( {} ), m_min( min ), m_max( max ), m_step( step )
	{
		m_name = name;

		m_name_size = text_size( name );

		m_var = var;
	}

	void c_slider::render( math::vec2_t& pos )
	{
		m_pos = pos;

		setup_style();

		handle_slide();

		const auto control_name_pos = math::vec2_t( m_pos.x + m_style.m_inner_padding, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f );

		/// Control name
		gui::text( control_name_pos, m_is_active ? m_style.m_col_text_hover : m_style.m_col_text, fmt::format( "{} ({})", m_name, static_cast<double>( m_var->get<float>() ) ) );

		/// Render slider
		render_slider();

		pos.y += m_size.y;
	}

	void c_slider::handle_input()
	{
		if ( !m_is_active )
			return;

		/// Decrease value
		if ( input::get_mouse().m_state == input::PRESSED )
		{
			push_action( gui::get_curtime() );

			m_did_increase = false;

			m_var->get<float>()--;
		}
		/// Increase value
		else if ( input::get_mouse().m_state_right == input::PRESSED )
		{
			push_action( gui::get_curtime() );

			m_did_increase = true;

			m_var->get<float>()++;
		}

		/// Clamp value
		m_var->get<float>() = std::clamp( m_var->get<float>(), m_min, m_max );
	}

	void c_slider::setup_style()
	{
		m_style.m_col_text = col_t( 220, 220, 220 );
		m_style.m_col_text_hover = col_t::palette_t::red();

		m_style.m_col_slider = col_t::palette_t::red();
		m_style.m_col_slider_inner = col_t::palette_t::black( 100 );
		m_style.m_col_slider_outline = col_t::palette_t::light_black();

		m_style.m_inner_padding = 4;

		m_style.m_slider_width = static_cast< int >( gui::get_size().x * 0.35f );
	}

	void c_slider::handle_slide()
	{
		if ( !m_is_active )
			return;

		/// Handle value changing when mouse is held down
		if ( m_did_increase )
		{
			/// Mouse is let go
			if ( input::get_mouse().m_state_right == input::IDLE )
				reset_action();

			const auto time_delta = std::clamp( get_curtime() - m_last_action, 0.f, 0.35f );
			/// Check if mosue was held for at least 200 ms
			if ( time_delta >= 0.35f )
			{
				m_var->get<float>()++;
			}
		}
		else
		{
			/// Mouse is let go
			if ( input::get_mouse().m_state == input::IDLE )
				reset_action();

			const auto time_delta = std::clamp( get_curtime() - m_last_action, 0.f, 0.35f );
			/// Check if mosue was held for at least 200 ms
			if ( time_delta >= 0.35f )
			{
				m_var->get<float>()--;
			}
		}

		m_var->get<float>() = std::clamp( m_var->get<float>(), m_min, m_max );
	}

	void c_slider::render_slider()
	{
		const auto combobox_pos = math::vec2_t( m_pos.x + m_size.x - m_style.m_inner_padding - m_style.m_slider_width, m_pos.y + m_size.y * 0.5f - m_name_size.y * 0.5f + 1 );
		const auto combobox_size = math::vec2_t( static_cast< float >( m_style.m_slider_width ), m_name_size.y - 4 );

		/// Combobox inner
		gui::rect_filled( combobox_pos, combobox_size, m_style.m_col_slider_inner );

		const auto factor = ( m_var->get<float>() - m_min ) / ( m_max - m_min );

		/// Current selected item
		gui::rect_filled( combobox_pos, { combobox_size.x * factor, combobox_size.y }, m_style.m_col_slider );

		/// Outline
		gui::rect( combobox_pos, combobox_size, m_style.m_col_slider_outline );
	}
}