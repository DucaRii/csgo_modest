#pragma once

#include "../math/math.hpp"
#include "controls.hpp"

namespace shared::gui
{
	void render();
	void handle_input();

	void setup_style();

	controls::c_tab* add_tab( std::string_view name );

	void set_active_tab( int id );
	int get_active_tab();

	void set_toggle_key( const int vk );
	void set_hold_key( const int vk );

	void toggle();
	bool is_open();

	void set_pos( const math::vec2_t& pos );
	math::vec2_t get_pos();

	void set_size( const math::vec2_t& size );
	math::vec2_t get_size();

	void set_name( std::string_view name );
	std::string_view get_name();

	int get_item_size();

	/// Helper functions that have to be externally initialized
	void setup_helper(
		const std::function<float()>& curtime,
		const std::function<float()>& frametime,
		const std::function<void( const math::vec2_t&, const math::vec2_t&, const col_t& )>& rect_filled,
		const std::function<void( const math::vec2_t&, const math::vec2_t&, const col_t& )>& rect,
		const std::function<void( const math::vec2_t&, const col_t& col, std::string_view )>& text,
		const std::function<math::vec2_t( std::string_view )>& text_size,
		const std::function<void()>& reset_clip,
		const std::function<void( const math::vec2_t&, const math::vec2_t&, bool )>& clip
	);

	float get_curtime();
	float get_frametime();

	void rect_filled( const math::vec2_t& pos, const math::vec2_t& size, const col_t& col );
	void rect( const math::vec2_t& pos, const math::vec2_t& size, const col_t& col );

	void text( const math::vec2_t& pos, const col_t& col, std::string_view text );
	math::vec2_t text_size( std::string_view text );

	void reset_clip();
	void clip( const math::vec2_t& pos, const math::vec2_t& size, bool override_clip = false );
}