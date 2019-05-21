#pragma once

namespace render
{
	namespace fonts
	{
		enum e_flags
		{
			FONT_RIGHT = 1 << 0,
			FONT_CENTER_X = 1 << 1,
			FONT_CENTER_Y = 1 << 2
		};

		void init();

		extern HFont m_main;
	}

	void init();
	void undo();

	shared::math::vec2_t get_screen_size();
	void get_screen_size( shared::math::vec2_t& size );

	void text( const HFont& font, const shared::math::vec2_t& pos, const shared::col_t& col, shared::bitflag_t flags, const char* txt );
	void text( const HFont& font, const shared::math::vec2_t& pos, const shared::col_t& col, shared::bitflag_t flags, const std::string& txt );

	shared::math::vec2_t text_size( const HFont& font, const char* txt );
	shared::math::vec2_t text_size( const HFont& font, const std::string& txt );

	void set_color( const shared::col_t& col );
	void set_color( const int r, const int g, const int b, const int a = 255 );
}