#pragma once

namespace render
{
	namespace fonts
	{
		enum e_flags
		{
			FONT_RIGHT = 1 << 0,
			FONT_CENTER_X = 1 << 1,
			FONT_CENTER_Y = 1 << 2,
		};

		void init();

		extern HFont m_main;
		extern HFont m_menu;
	}

	void init();
	void undo();

	math::vec2_t get_screen_size();
	void get_screen_size( math::vec2_t& size );

	void text( const HFont& font, const math::vec2_t& pos, const col_t& col, bitflag_t flags, const char* txt );
	void text( const HFont& font, const math::vec2_t& pos, const col_t& col, bitflag_t flags, std::string_view txt );

	math::vec2_t text_size( const HFont& font, const char* txt );
	math::vec2_t text_size( const HFont& font, std::string_view txt );

	void rect_filled( const math::vec2_t& pos, const math::vec2_t& size, const col_t& col );
	void rect( const math::vec2_t& pos, const math::vec2_t& size, const col_t& col );

	void line( const math::vec2_t& pos1, const math::vec2_t& pos2, const col_t& col );

	void circle_filled( const math::vec2_t& pos, const int radius, const int segments, const col_t& col );
	void circle( const math::vec2_t& pos, const int radius, const int segments, const col_t& col );

	void triangle_filled( const math::vec2_t& pos1, const math::vec2_t& pos2, const math::vec2_t& pos3, const col_t& col );

	void polygon( int count, math::vert_t* vertices, const col_t& col );

	void set_color( const col_t& col );
	void set_color( const int r, const int g, const int b, const int a = 255 );

	void clip( const math::vec2_t& pos, const math::vec2_t& size, bool override = false );
	void clip( RECT rec, bool override = false );
	void reset_clip();
	RECT get_current_clip();
}