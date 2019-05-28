#include "../shared.hpp"

namespace shared::gui
{
	int m_toggle_key = VK_INSERT;
	int m_hold_key = VK_MENU;

	size_t m_active_tab = 0;

	bool m_open = false;

	std::string_view m_name = "";

	math::vec2_t m_pos = {};
	math::vec2_t m_size = {};

	std::vector<std::shared_ptr<controls::c_tab>> m_tabs = {};

	struct style_t
	{
		col_t m_col_title_text;

		col_t m_col_frame_border;
		col_t m_col_frame_border_outline;

		col_t m_col_frame_inner;

		int m_border_size;
		int m_header_height;
	} m_style;

	void render()
	{
		if ( !is_open() )
			return;

		auto window_pos = m_pos - m_size * 0.5f;

		/// Border
		rect_filled( { window_pos.x - m_style.m_border_size, window_pos.y - m_style.m_header_height },
					 { m_size.x + m_style.m_border_size * 2, m_size.y + m_style.m_border_size + m_style.m_header_height },
					 m_style.m_col_frame_border );

		/// Outline
		rect( { window_pos.x - m_style.m_border_size, window_pos.y - m_style.m_header_height },
			  { m_size.x + m_style.m_border_size * 2, m_size.y + m_style.m_border_size + m_style.m_header_height },
			  m_style.m_col_frame_border_outline );

		/// Draw window title
		text( window_pos - math::vec2_t( 0.f, m_style.m_header_height - 2.f ), m_style.m_col_title_text, m_name );

		/// Inner frame
		rect_filled( window_pos, m_size, m_style.m_col_frame_inner );

		/// Inner outline
		rect( window_pos, m_size, m_style.m_col_frame_border_outline );

		/// Render tabs
		const auto scaled_size = m_size.x - 2;
		const auto tab_size = scaled_size / m_tabs.size();
		auto pos = window_pos + math::vec2_t( 1, 0 );
		for ( auto& tab : m_tabs )
		{
			tab->set_size( math::vec2_t( tab_size, static_cast< float >( get_item_size() ) ) );
			tab->render( pos );
		}
	}

	void handle_input()
	{
		for ( const auto& tab : m_tabs )
			tab->handle_input();
	}

	void setup_style()
	{
		m_style.m_col_title_text = col_t( 230, 230, 230 );

		m_style.m_col_frame_border = col_t::palette_t::grey();
		m_style.m_col_frame_border_outline = col_t( 5, 5, 5, 150 );

		m_style.m_col_frame_inner = col_t::palette_t::dark_grey();

		m_style.m_border_size = 6;
		m_style.m_header_height = 18;
	}

	controls::c_tab* add_tab( std::string_view name )
	{
		auto tab = std::make_shared<controls::c_tab>( name );

		/// Assign ID to new tab
		tab->set_id( m_tabs.size() );

		m_tabs.push_back( tab );

		return tab.get();
	}

	void set_active_tab( int id )
	{
		/// Perform "clamping"
		if ( id < 0 )
			id = static_cast< int >( m_tabs.size() ) - 1;
		else if ( id >= static_cast< int >( m_tabs.size() ) )
			id = 0;

		m_active_tab = id;
	}

	int get_active_tab()
	{
		return m_active_tab;
	}

	void set_toggle_key( const int vk )
	{
		m_toggle_key = vk;
	}

	void set_hold_key( const int vk )
	{
		m_hold_key = vk;
	}

	void toggle()
	{
		if ( input::get_key_info( m_toggle_key ).m_state == input::PRESSED )
			m_open = !m_open;
	}

	bool is_open()
	{
		return m_open || input::get_key_info( m_hold_key ).m_state != input::IDLE;
	}

	void set_pos( const math::vec2_t & pos )
	{
		m_pos = pos;
	}

	math::vec2_t get_pos()
	{
		return m_pos;
	}

	void set_size( const math::vec2_t & size )
	{
		m_size = { size.x, size.y * get_item_size() };
	}

	math::vec2_t get_size()
	{
		return m_size;
	}

	void set_name( std::string_view name )
	{
		m_name = name;
	}

	std::string_view get_name()
	{
		return m_name;
	}

	int get_item_size()
	{
		return 18;
	}

	/// Helper functions that have to be externally initialized
	std::function<float()> m_curtime_fn;
	std::function<float()> m_frametime_fn;
	std::function<void( const math::vec2_t&, const math::vec2_t&, const col_t& )> m_rect_filled_fn;
	std::function<void( const math::vec2_t&, const math::vec2_t&, const col_t& )> m_rect_fn;
	std::function<void( const math::vec2_t&, const col_t & col, std::string_view )> m_text_fn;
	std::function<math::vec2_t( std::string_view )> m_text_size_fn;
	std::function<void()> m_reset_clip_fn;
	std::function<void( const math::vec2_t&, const math::vec2_t&, bool )> m_clip_fn;

	void setup_helper( const std::function<float()> & curtime,
					   const std::function<float()> & frametime,
					   const std::function<void( const math::vec2_t&, const math::vec2_t&, const col_t& )> & rect_filled,
					   const std::function<void( const math::vec2_t&, const math::vec2_t&, const col_t& )> & rect,
					   const std::function<void( const math::vec2_t&, const col_t & col, std::string_view )> & text,
					   const std::function<math::vec2_t( std::string_view )> & text_size,
					   const std::function<void()> & reset_clip,
					   const std::function<void( const math::vec2_t&, const math::vec2_t&, bool )> & clip )
	{
		m_curtime_fn = curtime;
		m_frametime_fn = frametime;
		m_rect_filled_fn = rect_filled;
		m_rect_fn = rect;
		m_text_fn = text;
		m_text_size_fn = text_size;
		m_reset_clip_fn = reset_clip;
		m_clip_fn = clip;
	}

	float get_curtime()
	{
		return m_curtime_fn();
	}

	float get_frametime()
	{
		return m_frametime_fn();
	}

	void rect_filled( const math::vec2_t & pos, const math::vec2_t & size, const col_t & col )
	{
		m_rect_filled_fn( pos, size, col );
	}

	void rect( const math::vec2_t & pos, const math::vec2_t & size, const col_t & col )
	{
		m_rect_fn( pos, size, col );
	}

	void text( const math::vec2_t & pos, const col_t & col, std::string_view text )
	{
		m_text_fn( pos, col, text );
	}

	math::vec2_t text_size( std::string_view text )
	{
		return m_text_size_fn( text );
	}

	void reset_clip()
	{
		return m_reset_clip_fn();
	}

	void clip( const math::vec2_t & pos, const math::vec2_t & size, bool override_clip )
	{
		return m_clip_fn( pos, size, override_clip );
	}
}