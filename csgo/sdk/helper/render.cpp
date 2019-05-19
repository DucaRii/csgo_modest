#include "../../csgo.hpp"


#define SHIDWORD(x)  (*( ( int32_t* )&( x ) + 1 ) )
namespace render
{
	namespace fonts
	{
		HFont m_main;

		void init()
		{
			const auto font = [ & ]( HFont & font, const char* name, const int size, const int weight, const int flags ) -> void
			{
				font = ctx::csgo.font_manager()->CreateFont( SHIDWORD( *ctx::csgo.font_manager() ) );
				ctx::csgo.font_manager()->SetFontGlyphSet( font, name, size, weight, NULL, NULL, flags );
			};

			font( m_main, "Arial", 18, 400, FONTFLAG_DROPSHADOW );
		}
	}

	shared::math::vec2_t m_screen{};
	bool m_init{};

	void init( ISurface* render )
	{
		if ( m_init )
			return;

		int x, y;
		ctx::csgo.engine()->GetScreenSize( x, y );
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
	}

	void text( const HFont& font, const shared::math::vec2_t& pos, const shared::col_t& col, shared::bitflag_t flags, const std::string& txt )
	{
		text( font, pos, col, flags, txt.c_str() );
	}

	shared::math::vec2_t text_size( const HFont& font, const char* txt )
	{
		auto height = ctx::csgo.surface()->GetFontTall( font );

		auto width = 0;
		auto length = strlen( txt ) - 1;
		for ( auto i = 0u; i < length; i++ )
			width += ctx::csgo.surface()->GetCharacterWidth( font, txt[ i ] );

		return shared::math::vec2_t( static_cast< float >( width ),
									 static_cast< float >( height ) );
	}

	shared::math::vec2_t text_size( const HFont & font, const std::string & txt )
	{
		return text_size( font, txt.c_str() );
	}
}