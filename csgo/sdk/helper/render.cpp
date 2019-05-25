#include "../../csgo.hpp"

namespace render
{
	namespace fonts
	{
		HFont m_main;
		HFont m_menu;

		void init()
		{
			const auto font = [ & ]( HFont & font, const char* name, const int size, const int weight, const int flags ) -> void
			{
				font = ctx::csgo.surface->CreateFont_();
				ctx::csgo.font_manager->SetFontGlyphSet( font, name, size, weight, NULL, NULL, flags );
			};

			font( m_main, "Arial", 18, 400, FONTFLAG_DROPSHADOW );
			font( m_menu, "Arial", 14, 400, FONTFLAG_DROPSHADOW );
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

		ctx::csgo.surface->DrawColoredText( font,
											static_cast< int >( text_pos.x ),
											static_cast< int >( text_pos.y ),
											col.r(), col.g(), col.b(), col.a(), txt );
	}

	void text( const HFont& font, const shared::math::vec2_t& pos, const shared::col_t& col, shared::bitflag_t flags, std::string_view txt )
	{
		text( font, pos, col, flags, txt.data() );
	}

	shared::math::vec2_t text_size( const HFont& font, std::string_view txt )
	{
		auto width = 0,
			height = 0;

		auto str = std::wstring( txt.begin(), txt.end() );

		ctx::csgo.font_manager->GetTextSize( font, str.c_str(), width, height );

		return shared::math::vec2_t( static_cast< float >( width ),
									 static_cast< float >( height ) );
	}

	void rect_filled( const shared::math::vec2_t& pos, const shared::math::vec2_t& size, const shared::col_t& col )
	{
		set_color( col );
		ctx::csgo.surface->DrawFilledRect( static_cast< int >( pos.x ),
										   static_cast< int >( pos.y ),
										   static_cast< int >( pos.x + size.x ),
										   static_cast< int >( pos.y + size.y ) );
	}

	void rect( const shared::math::vec2_t & pos, const shared::math::vec2_t & size, const shared::col_t & col )
	{
		set_color( col );
		ctx::csgo.surface->DrawOutlinedRect( static_cast< int >( pos.x ),
											 static_cast< int >( pos.y ),
											 static_cast< int >( pos.x + size.x ),
											 static_cast< int >( pos.y + size.y ) );
	}

	void line( const shared::math::vec2_t & pos1, const shared::math::vec2_t & pos2, const shared::col_t & col )
	{
		set_color( col );
		ctx::csgo.surface->DrawLine( static_cast< int >( pos1.x ),
									 static_cast< int >( pos1.y ),
									 static_cast< int >( pos2.x ),
									 static_cast< int >( pos2.y ) );
	}

	void circle_filled( const shared::math::vec2_t & pos, const int radius, const int segments, const shared::col_t & col )
	{
		static std::vector<shared::math::vert_t> vertices{};

		float step = static_cast< float >( M_PI ) * 2.0f / segments;

		for ( float a = 0; a < M_PI * 2.0f; a += step )
			vertices.push_back( shared::math::vert_t( shared::math::vec2_t( radius * cosf( a ) + pos.x,
															  radius * sinf( a ) + pos.y ) ) );

		polygon( segments, vertices.data(), col );

		vertices.clear();
	}

	void circle( const shared::math::vec2_t & pos, const int radius, const int segments, const shared::col_t & col )
	{
		set_color( col );
		ctx::csgo.surface->DrawOutlinedCircle( static_cast< int >( pos.x ),
											   static_cast< int >( pos.y ),
											   radius,
											   segments );
	}

	void triangle_filled( const shared::math::vec2_t & pos1, const shared::math::vec2_t & pos2, const shared::math::vec2_t & pos3, const shared::col_t & col )
	{
		static shared::math::vert_t triangle_vert[ 3 ];

		triangle_vert[ PITCH ].init( pos1 );
		triangle_vert[ YAW ].init( pos2 );
		triangle_vert[ ROLL ].init( pos3 );

		polygon( 3, triangle_vert, col );
	}

	void polygon( int count, shared::math::vert_t* vertices, const shared::col_t & col )
	{
		static int texture_id;

		if ( !ctx::csgo.surface->IsTextureIDValid( texture_id ) )
			texture_id = ctx::csgo.surface->CreateNewTextureID();

		set_color( col );
		ctx::csgo.surface->DrawSetTexture( texture_id );
		ctx::csgo.surface->DrawTexturedPolygon( count, vertices );
	}

	inline shared::math::vec2_t text_size( const HFont & font, const char* txt )
	{
		return text_size( font, std::string( txt ) );
	}

	void set_color( const shared::col_t & col )
	{
		ctx::csgo.surface->DrawSetColor( col.r(), col.g(), col.b(), col.a() );
	}

	void set_color( const int r, const int g, const int b, const int a )
	{
		ctx::csgo.surface->DrawSetColor( r, g, b, a );
	}
}