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

			font( m_main, "Arial", 13, 400, FONTFLAG_OUTLINE );
			font( m_menu, "Arial", 14, 400, FONTFLAG_DROPSHADOW );
		}
	}

	math::vec2_t m_screen{};

	bool m_init{};

	std::deque<RECT> m_clip_records = {};

	void init()
	{
		int x, y;
		ctx::csgo.engine->GetScreenSize( x, y );
		m_screen = math::vec2_t( static_cast< float >( x ), static_cast< float >( y ) );

		if ( m_init )
			return;

		fonts::init();

		m_init = true;
	}

	void undo()
	{
		m_init = false;
	}

	math::vec2_t get_screen_size()
	{
		return m_screen;
	}

	void get_screen_size( math::vec2_t& size )
	{
		size = get_screen_size();
	}

	void text( const HFont& font, const math::vec2_t& pos, const col_t& col, bitflag_t flags, const char* txt )
	{
		/// Hey laxol I knew you would come here, fuck you.
		auto text_pos = pos;

		if ( !flags.is_empty() )
		{
			const auto size = text_size( font, txt );

			if ( flags.has_flag( render::fonts::FONT_RIGHT ) )
				text_pos.x -= size.x;

			if ( flags.has_flag( render::fonts::FONT_CENTER_X ) )
				text_pos.x -= size.x * 0.5f;

			if ( flags.has_flag( render::fonts::FONT_CENTER_Y ) )
				text_pos.y -= size.y * 0.5f;
		}

		ctx::csgo.surface->DrawColoredText( font,
											static_cast< int >( text_pos.x ),
											static_cast< int >( text_pos.y ),
											col.r(), col.g(), col.b(), col.a(), txt );
	}

	void text( const HFont& font, const math::vec2_t& pos, const col_t& col, bitflag_t flags, std::string_view txt )
	{
		text( font, pos, col, flags, txt.data() );
	}

	math::vec2_t text_size( const HFont& font, std::string_view txt )
	{
		auto width = 0,
			height = 0;

		auto str = std::wstring( txt.begin(), txt.end() );

		ctx::csgo.font_manager->GetTextSize( font, str.c_str(), width, height );

		return math::vec2_t( static_cast< float >( width ),
							 static_cast< float >( height ) );
	}

	inline math::vec2_t text_size( const HFont& font, const char* txt )
	{
		return text_size( font, std::string_view( txt ) );
	}

	void rect_filled( const math::vec2_t& pos, const math::vec2_t& size, const col_t& col )
	{
		set_color( col );
		ctx::csgo.surface->DrawFilledRect( static_cast< int >( pos.x ),
										   static_cast< int >( pos.y ),
										   static_cast< int >( pos.x + size.x ),
										   static_cast< int >( pos.y + size.y ) );
	}

	void rect( const math::vec2_t & pos, const math::vec2_t & size, const col_t & col )
	{
		set_color( col );
		ctx::csgo.surface->DrawOutlinedRect( static_cast< int >( pos.x ),
											 static_cast< int >( pos.y ),
											 static_cast< int >( pos.x + size.x ),
											 static_cast< int >( pos.y + size.y ) );
	}

	void line( const math::vec2_t & pos1, const math::vec2_t & pos2, const col_t & col )
	{
		set_color( col );
		ctx::csgo.surface->DrawLine( static_cast< int >( pos1.x ),
									 static_cast< int >( pos1.y ),
									 static_cast< int >( pos2.x ),
									 static_cast< int >( pos2.y ) );
	}

	void circle_filled( const math::vec2_t & pos, const int radius, const int segments, const col_t & col )
	{
		static std::vector<math::vert_t> vertices{};

		float step = static_cast< float >( M_PI ) * 2.0f / segments;

		for ( float a = 0; a < M_PI * 2.0f; a += step )
			vertices.push_back( math::vert_t( math::vec2_t( radius * cosf( a ) + pos.x,
															radius * sinf( a ) + pos.y ) ) );

		polygon( segments, vertices.data(), col );

		vertices.clear();
	}

	void circle( const math::vec2_t & pos, const int radius, const int segments, const col_t & col )
	{
		set_color( col );
		ctx::csgo.surface->DrawOutlinedCircle( static_cast< int >( pos.x ),
											   static_cast< int >( pos.y ),
											   radius,
											   segments );
	}

	void triangle_filled( const math::vec2_t & pos1, const math::vec2_t & pos2, const math::vec2_t & pos3, const col_t & col )
	{
		static math::vert_t triangle_vert[ 3 ];

		triangle_vert[ PITCH ].init( pos1 );
		triangle_vert[ YAW ].init( pos2 );
		triangle_vert[ ROLL ].init( pos3 );

		polygon( 3, triangle_vert, col );
	}

	void polygon( int count, math::vert_t * vertices, const col_t & col )
	{
		static int texture_id;

		if ( !ctx::csgo.surface->IsTextureIDValid( texture_id ) )
			texture_id = ctx::csgo.surface->CreateNewTextureID();

		set_color( col );
		ctx::csgo.surface->DrawSetTexture( texture_id );
		ctx::csgo.surface->DrawTexturedPolygon( count, vertices );
	}

	void set_color( const col_t & col )
	{
		ctx::csgo.surface->DrawSetColor( col.r(), col.g(), col.b(), col.a() );
	}

	void set_color( const int r, const int g, const int b, const int a )
	{
		ctx::csgo.surface->DrawSetColor( r, g, b, a );
	}

	void clip( const math::vec2_t & pos, const math::vec2_t & size, bool override )
	{
		RECT rec;
		rec.left = static_cast< LONG >( pos.x );
		rec.top = static_cast< LONG >( pos.y );
		rec.right = static_cast< LONG >( pos.x + size.x + 1 );
		rec.bottom = static_cast< LONG >( pos.y + size.y + 1 );

		if ( !override && !m_clip_records.empty() )
		{
			auto& last_record = m_clip_records.back();
			rec.left = std::clamp( rec.left, last_record.left, last_record.right );
			rec.right = std::clamp( rec.right, last_record.left, last_record.right );
			rec.top = std::clamp( rec.top, last_record.top, last_record.bottom );
			rec.bottom = std::clamp( rec.bottom, last_record.top, last_record.bottom );
		}

		m_clip_records.push_back( rec );

		ctx::csgo.surface->SetClipRect( rec.left, rec.top, rec.right, rec.bottom );
	}

	void clip( RECT rec, bool override )
	{
		if ( !override && !m_clip_records.empty() )
		{
			auto& last_record = m_clip_records.back();
			rec.left = std::clamp( rec.left, last_record.left, last_record.right );
			rec.right = std::clamp( rec.right, last_record.left, last_record.right );
			rec.top = std::clamp( rec.top, last_record.top, last_record.bottom );
			rec.bottom = std::clamp( rec.bottom, last_record.top, last_record.bottom );
		}

		m_clip_records.push_back( rec );

		ctx::csgo.surface->SetClipRect( rec.left, rec.top, rec.right, rec.bottom );
	}

	void reset_clip()
	{
		m_clip_records.pop_back();

		/// If we have a scissor rect from earlier, use that one
		if ( !m_clip_records.empty() )
		{
			auto& latest_record = m_clip_records.back();
			ctx::csgo.surface->SetClipRect( latest_record.left, latest_record.top, latest_record.right, latest_record.bottom );
		}
		else /// Reset to fullscreen
			ctx::csgo.surface->SetClipRect( 0, 0, static_cast< int >( m_screen.x ), static_cast< int >( m_screen.y ) );
	}

	RECT get_current_clip()
	{
		if ( m_clip_records.empty() )
		{
			RECT rec;
			rec.left = 0;
			rec.top = 0;
			rec.right = static_cast< int >( render::get_screen_size().x );
			rec.bottom = static_cast< int >( render::get_screen_size().y );

			return rec;
		}

		return m_clip_records.back();
	}
}
