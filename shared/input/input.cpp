#include "../shared.hpp"

namespace shared::input
{
	HWND m_window = NULL;
	WNDPROC m_original_wndproc = nullptr;

	char m_last_char;
	std::array<key_info_t, 256> m_key_info{};

	mouse_info_t m_mouse_info;

	void init( std::wstring_view window )
	{
		/// Input was already initialized ?
		if ( m_window )
			return;

		m_window = FindWindowW( window.data(), NULL );
		if ( !m_window )
			throw std::runtime_error( "input::init - Failed to find input window" );

		m_original_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongW( m_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hook ) ) );
		if ( !m_original_wndproc )
			throw std::runtime_error( "input::init - Failed to set new WndProc" );
	}

	void undo()
	{
		if ( m_original_wndproc )
			SetWindowLongW( m_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( m_original_wndproc ) );

		m_original_wndproc = NULL;
	}

	bool handle_mouse( const UINT msg )
	{
		switch ( msg )
		{
			/// Left mouse button
			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK:
				if ( m_mouse_info.m_state == e_state::IDLE )
					m_mouse_info.m_state = e_state::PRESSED;
				return true;
			case WM_LBUTTONUP:
				m_mouse_info.m_state = e_state::IDLE;
				return true;

				/// Right mouse button
			case WM_RBUTTONDOWN:
			case WM_RBUTTONDBLCLK:
				if ( m_mouse_info.m_state_right == e_state::IDLE )
					m_mouse_info.m_state_right = e_state::PRESSED;
				return true;
			case WM_RBUTTONUP:
				m_mouse_info.m_state_right = e_state::IDLE;
				return true;
			default:
				break;
		}

		/// Mouse has been pressed for more than 1 input tick
		if ( m_mouse_info.m_state == e_state::PRESSED )
			m_mouse_info.m_state = e_state::HELD;

		if ( m_mouse_info.m_state_right == e_state::PRESSED )
			m_mouse_info.m_state_right = e_state::HELD;

		return msg == WM_MOUSEMOVE || msg == WM_NCMOUSEMOVE;
	}

	bool handle_keyboard( const UINT msg, const WPARAM param )
	{
		auto changed_state = false;

		for ( auto i = 0; i < 256; i++ )
		{
			if ( m_key_info.at( i ).m_state == e_state::PRESSED )
			{
				m_key_info.at( i ).m_state = e_state::HELD;
				changed_state = true;
			}
		}

		switch ( msg )
		{
			/// Input character
			case WM_CHAR:
				if ( param > 0 && param < 0x10000 )
					m_last_char = static_cast< char >( param );
				return true;

				/// "Normal" keys
			case WM_KEYDOWN:
				if ( param >= 0 && param < 256 )
					m_key_info.at( param ).m_state = e_state::PRESSED;
				return true;
			case WM_KEYUP:
				if ( param >= 0 && param < 256 )
				{
					m_key_info.at( param ).m_state = e_state::IDLE;
				}
				return true;

				/// Side mouse buttons
			case WM_XBUTTONDOWN:
			case WM_XBUTTONDBLCLK:
				if ( GET_XBUTTON_WPARAM( param ) & XBUTTON1 )
					m_key_info.at( VK_XBUTTON1 ).m_state = e_state::PRESSED;
				else if ( GET_XBUTTON_WPARAM( param ) & XBUTTON2 )
					m_key_info.at( VK_XBUTTON2 ).m_state = e_state::PRESSED;
				return true;
			case WM_XBUTTONUP:
				if ( GET_XBUTTON_WPARAM( param ) & XBUTTON1 )
					m_key_info.at( VK_XBUTTON1 ).m_state = e_state::IDLE;
				else if ( GET_XBUTTON_WPARAM( param ) & XBUTTON2 )
					m_key_info.at( VK_XBUTTON2 ).m_state = e_state::IDLE;
				return true;

				/// System keys
			case WM_SYSKEYDOWN:
				if ( param >= 0 && param < 256 )
					m_key_info.at( param ).m_state = e_state::PRESSED;
				return true;
			case WM_SYSKEYUP:
				if ( param >= 0 && param < 256 )
					m_key_info.at( param ).m_state = e_state::IDLE;
				return true;

				/// Middle button
			case WM_MBUTTONDOWN:
			case WM_MBUTTONDBLCLK:
				m_key_info.at( VK_MBUTTON ).m_state = e_state::PRESSED;
				return true;
			case WM_MBUTTONUP:
				m_key_info.at( VK_MBUTTON ).m_state = e_state::IDLE;
				return true;

				/// Left mouse button
			case WM_LBUTTONDOWN:
			case WM_LBUTTONDBLCLK:
				m_key_info.at( VK_LBUTTON ).m_state = e_state::PRESSED;
				return true;
			case WM_LBUTTONUP:
				m_key_info.at( VK_LBUTTON ).m_state = e_state::IDLE;
				return true;

				/// Right mouse button
			case WM_RBUTTONDOWN:
			case WM_RBUTTONDBLCLK:
				m_key_info.at( VK_RBUTTON ).m_state = e_state::PRESSED;
				return true;
			case WM_RBUTTONUP:
				m_key_info.at( VK_RBUTTON ).m_state = e_state::IDLE;
				return true;

				/// Mouse wheel
			case WM_MOUSEWHEEL:
				m_mouse_info.m_scroll = GET_WHEEL_DELTA_WPARAM( param ) / WHEEL_DELTA;
				return true;
			default:;
		}

		return changed_state;
	}

	/// Mouse info
	void update_mouse()
	{
		POINT p;
		if ( !GetCursorPos( &p ) )
			return;

		ScreenToClient( m_window, &p );

		m_mouse_info.m_pos = {
			static_cast< float >( p.x ),
			static_cast< float >( p.y ) };
	}

	mouse_info_t& get_mouse()
	{
		return m_mouse_info;
	}

	void reset_mouse()
	{
		m_mouse_info.m_state = e_state::IDLE;
		m_mouse_info.m_state_right = e_state::IDLE;
		m_mouse_info.m_scroll = 0;
	}

	bool mouse_in_bounds( const math::vec2_t& pos, const math::vec2_t& size )
	{
		const auto mouse_pos = m_mouse_info.m_pos;

		return mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + size.x
			&& mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + size.y;
	}

	bool mouse_in_bounds( const math::vec4_t& bounds )
	{
		return mouse_in_bounds( bounds.get_pos(), bounds.get_size() );
	}

	/// Key info
	key_info_t& get_key_info( const int key )
	{
		return m_key_info.at( key );
	}

	std::string_view get_key_name( const int key )
	{
		return "TODO";
	}

	char get_last_char()
	{
		return m_last_char;
	}

	void clear_char()
	{
		m_last_char = '\0';
	}

	unsigned long WINAPI hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
	{
		const auto handled_mouse = handle_mouse( msg );
		const auto handled_keyboard = handle_keyboard( msg, wparam );

		gui::toggle();

		if ( gui::is_open() && ( handled_mouse || handled_keyboard ) )
		{
			gui::handle_input();

			get_mouse().reset_scroll();

			return false;
		}

		const auto ret = CallWindowProc( m_original_wndproc, hwnd, msg, wparam, lparam );

		return ret && !handled_keyboard && !handled_mouse;
	}
}