#pragma once

#include "../math/datatypes/vec2_t.hpp"
#include "../math/datatypes/vec4_t.hpp"

namespace shared::input
{
	enum e_mouse_state
	{
		IDLE,
		PRESSED,
		HELD
	};

	struct mouse_info_t
	{
		mouse_info_t() :
			m_state( e_mouse_state::IDLE ),
			m_state_right( e_mouse_state::IDLE ),
			m_scroll( 0 ),
			m_pos( math::vec2_t{ } )
		{}

		void reset_scroll()
		{
			m_scroll = 0;
		}

		e_mouse_state m_state;
		e_mouse_state m_state_right;
		int m_scroll;

		math::vec2_t m_pos;
	};

	struct key_info_t
	{
		bool pressed;
		bool held;
	};

	void init( const std::string& window_name );

	/// Message handling
	bool handle_mouse( const UINT msg );
	bool handle_keyboard( const UINT msg, const WPARAM param );
	unsigned long WINAPI hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );

	/// Mouse info
	void update_mouse();
	mouse_info_t& get_mouse();
	void reset_mouse();

	bool mouse_in_bounds( const math::vec2_t& pos, const math::vec2_t& size );
	bool mouse_in_bounds( const math::vec4_t& bounds );

	/// Key info
	key_info_t& get_key_info( const int key );
	std::string get_key_name( const int key );
	char get_last_char();
	void clear_char();

}