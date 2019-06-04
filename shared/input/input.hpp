#pragma once

#include "../math/datatypes/vec2_t.hpp"
#include "../math/datatypes/vec4_t.hpp"

namespace shared::input
{
	/// <summary>
	/// Different states used for mouse/key info
	/// </summary>
	enum e_state
	{
		IDLE,
		PRESSED,
		HELD
	};

	struct mouse_info_t
	{
		/// <summary>
		/// Constructs mouse info with default values
		/// </summary>
		mouse_info_t() :
			m_state( e_state::IDLE ),
			m_state_right( e_state::IDLE ),
			m_scroll( 0 ),
			m_pos( math::vec2_t{ } )
		{}

		/// <summary>
		/// Reset scroll amount
		/// </summary>
		void reset_scroll()
		{
			m_scroll = 0;
		}

		/// <summary>
		/// State of of the left mouse button ( IDLE, PRESSED, HELD )
		/// </summary>
		e_state m_state;

		/// <summary>
		/// State of of the right mouse button ( IDLE, PRESSED, HELD )
		/// </summary>
		e_state m_state_right;

		/// <summary>
		/// Scroll amount. Negative means scrolling up and the other way around
		/// </summary>
		int m_scroll;

		/// <summary>
		/// Current mouse position
		/// </summary>
		math::vec2_t m_pos;
	};

	struct key_info_t
	{
		/// <summary>
		/// State of key ( IDLE, PRESSED, HELD )
		/// </summary>
		e_state m_state;

		/// <summary>
		/// Checks if key is pressed
		/// </summary>
		bool is_pressed()
		{
			bool pressed = m_state == PRESSED;
			if ( pressed )
				m_state = HELD;

			return pressed;
		}

		/// <summary>
		/// Checks if key is held
		/// </summary>
		bool is_held()
		{
			return m_state == HELD;
		}
	};

	/// <summary>
	/// Initializes input handler with given window class
	/// </summary>
	/// <param name="window">Window class name</param>
	/// <returns>Returns true if it was successful</returns>
	void init( std::wstring_view window );

	/// <summary>
	/// Restores original WndProc
	/// </summary>
	void undo();

	/// Message handling

	/// <summary>
	/// Handles mouse input message and fills the local mouse info
	/// </summary>
	/// <param name="msg">Mouse message emitted from WndProc</param>
	/// <returns>Returns true if mouse input was handled</returns>
	bool handle_mouse( const UINT msg );

	/// <summary>
	/// Handles keyboard input message and fills the right key info
	/// </summary>
	/// <param name="msg">Key message emitted from WndProc</param>
	/// <param name="param">Additional message info dependent on the msg parameter</param>
	/// <returns>Returns true if keyboard input was handled</returns>
	bool handle_keyboard( const UINT msg, const WPARAM param );

	/// <summary>
	/// All Windows input goes through this function so it can just be yoinked from there
	/// </summary>
	/// <param name="hwnd">A handle to the window</param>
	/// <param name="msg">The message received</param>
	/// <param name="wparam">Additional message info dependent on the msg parameter</param>
	/// <param name="lparam">Additional message info dependent on the msg parameter</param>
	/// <returns>Result of the message processing and depends on the message sent</returns>
	unsigned long WINAPI hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );

	/// Mouse info

	/// <summary>
	/// Updates mouse position
	/// </summary>
	void update_mouse();

	/// <summary>
	/// Gets mouse info
	/// </summary>
	mouse_info_t& get_mouse();

	/// <summary>
	/// Reset mouse key states + scroll amount
	/// </summary>
	void reset_mouse();

	/// <summary>
	/// Checks if current mouse position is within specified bounds
	/// </summary>
	/// <param name="pos">Bounds start</param>
	/// <param name="size">Bounds size</param>
	/// <returns>Returns true if mouse position is within specified bounds</returns>
	bool mouse_in_bounds( const math::vec2_t& pos, const math::vec2_t& size );

	/// <summary>
	/// Checks if current mouse position is within specified bounds
	/// </summary>
	/// <param name="bounds">Bounds</param>
	/// <returns>Returns true if mouse position is within specified bounds</returns>
	bool mouse_in_bounds( const math::vec4_t& bounds );

	/// Key info

	/// <summary>
	/// Returns key info of given key
	/// </summary>
	/// <param name="key">Virtual key code of wished key info</param>
	/// <returns>Returns key info object</returns>
	key_info_t& get_key_info( const int key );

	/// <summary>
	/// Returns key name of given key
	/// </summary>
	/// <param name="key">Virtual key code of wished key name</param>
	/// <returns>Returns key name</returns>
	std::string_view get_key_name( const int key );

	/// <summary>
	/// Returns last char input by keyboard
	/// </summary>
	/// <returns>Last char entered by keyboard</returns>
	char get_last_char();

	/// <summary>
	/// Clears last char received
	/// </summary>
	void clear_char();
}