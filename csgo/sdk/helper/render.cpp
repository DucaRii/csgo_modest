#include "../../csgo.hpp"

namespace render
{
	namespace fonts
	{
		HFont m_main;

		void init()
		{
			const auto font = [ & ]( HFont & font, const char* name, const int size, const int weight, const int flags ) -> void
			{
				font = ctx::csgo.font_manager->CreateFont( ( *( ( int32_t* ) & ( *ctx::csgo.font_manager ) + 1 ) ) );
				ctx::csgo.font_manager->SetFontGlyphSet( font, name, size, weight, NULL, NULL, flags );
			};

			font( m_main, "Arial", 18, 400, FONTFLAG_DROPSHADOW );
		}
	}

	shared::math::vec2_t m_screen{};
	bool m_init{};

	void init()
	{
		if ( m_init )
			return;

		int x, y;
		ctx::csgo.engine->GetScreenSize( x, y );
		m_screen = shared::math::vec2_t( static_cast< float >( x ), static_cast< float >( y ) );

		fonts::init();

		m_init = true;
	}

	void undo()
	{
		m_init = false;
	}

	shared::math::vec2_t get_screen_size()
	{
		return m_screen;
	}

	void get_screen_size( shared::math::vec2_t& size )
	{
		size = get_screen_size();
	}

	void text( const HFont& font, const shared::math::vec2_t& pos, const shared::col_t& col, shared::bitflag_t flags, const char* txt )
	{
		/// Hey laxol I knew you would come here, fuck you.
		auto text_pos = pos;

		if ( !flags.is_empty() )
		{
			const auto size = text_size( font, txt );

			if ( flags.has_flag( render::fonts::FONT_RIGHT ) )
				text_pos.x -= size.x;

			if ( flags.has_flag( render::fonts::FONT_CENTER_X ) )
				text_pos.x += size.x * 0.5f;

			if ( flags.has_flag( render::fonts::FONT_CENTER_Y ) )
				text_pos.y -= size.y * 0.5f;
		}

		ctx::csgo.surface->DrawColoredText( font, text_pos.x, text_pos.y, col.r(), col.g(), col.b(), col.a(), txt );
	}

	void text( const HFont& font, const shared::math::vec2_t& pos, const shared::col_t& col, shared::bitflag_t flags, const std::string& txt )
	{
		text( font, pos, col, flags, txt.c_str() );
	}

	shared::math::vec2_t text_size( const HFont& font, const std::string& txt )
	{
		auto width = 0,
			height = 0;

		auto str = std::wstring( txt.begin(), txt.end() );

		ctx::csgo.font_manager->GetTextSize( font, str.c_str(), width, height );

		return shared::math::vec2_t( static_cast< float >( width ),
									 static_cast< float >( height ) );
	}

	inline shared::math::vec2_t text_size( const HFont & font, const char* txt )
	{
		return text_size( font, std::string( txt ) );
	}

	void set_color( const shared::col_t& col )
	{
		ctx::csgo.surface->DrawSetColor( col.r(), col.g(), col.b(), col.a() );
	}

	void set_color( const int r, const int g, const int b, const int a )
	{
		ctx::csgo.surface->DrawSetColor( r, g, b, a );
	}
}