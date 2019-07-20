#pragma once

#include "../../context/mem.hpp"

typedef unsigned long HFont;

#ifdef CreateFont
#undef CreateFont
#endif

enum FontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

struct ISurface
{
	CUSTOM_VFUNC( DrawSetColor( int r, int g, int b, int a ), void( __thiscall* )( void*, int, int, int, int ), ctx::mem.ISurface.DrawSetColor )( r, g, b, a );
	CUSTOM_VFUNC( DrawFilledRect( int x, int y, int x1, int y1 ), void( __thiscall* )( void*, int, int, int, int ), ctx::mem.ISurface.DrawFilledRect )( x, y, x1, y1 );
	CUSTOM_VFUNC( DrawOutlinedRect( int x, int y, int x1, int y1 ), void( __thiscall* )( void*, int, int, int, int ), ctx::mem.ISurface.DrawOutlinedRect )( x, y, x1, y1 );
	CUSTOM_VFUNC( DrawLine( int x, int y, int x1, int y1 ), void( __thiscall* )( void*, int, int, int, int ), ctx::mem.ISurface.DrawLine )( x, y, x1, y1 );
	CUSTOM_VFUNC( DrawSetTexture( int id ), void( __thiscall* )( void*, int ), ctx::mem.ISurface.DrawSetTexture )( id );
	CUSTOM_VFUNC( CreateNewTextureID( bool procedural = false ), int( __thiscall* )( void*, bool ), ctx::mem.ISurface.CreateNewTextureID )( procedural );
	CUSTOM_VFUNC( IsTextureIDValid( int id ), bool( __thiscall* )( void*, int ), ctx::mem.ISurface.IsTextureIDValid )( id );
	CUSTOM_VFUNC( CreateFont_(), HFont( __thiscall* )( void* ), ctx::mem.ISurface.CreateFont_ )( );
	CUSTOM_VFUNC( GetFontTall( HFont font ), int( __thiscall* )( void*, HFont ), ctx::mem.ISurface.GetFontTall )( font );
	CUSTOM_VFUNC( GetCharacterWidth( HFont font, char ch ), int( __thiscall* )( void*, HFont, char ), ctx::mem.ISurface.GetCharacterWidth )( font, ch );
	CUSTOM_VFUNC( DrawOutlinedCircle( int x, int y, int radius, int segments ), void( __thiscall* )( void*, int, int, int, int ), ctx::mem.ISurface.DrawOutlinedCircle )( x, y, radius, segments );
	CUSTOM_VFUNC( DrawFilledRectFade( int x, int y, int x1, int y1, uint32_t alpha, uint32_t alpha1, bool horizontal ), void( __thiscall* )( void*, int, int, int, int, size_t, size_t, bool ), ctx::mem.ISurface.DrawFilledRectFade )( x, y, x1, y1, alpha, alpha1, horizontal );
	CUSTOM_VFUNC( DrawTexturedPolygon( int count, math::vert_t* vertices, bool clip = true ), void( __thiscall* )( void*, int, math::vert_t*, bool ), ctx::mem.ISurface.DrawTexturedPolygon )( count, vertices, clip );
	CUSTOM_VFUNC( GetClipRect( int& x, int& y, int& x1, int& y1 ), void( __thiscall* )( void*, int&, int&, int&, int& ), ctx::mem.ISurface.GetClipRect )( x, y, x1, y1 );
	CUSTOM_VFUNC( SetClipRect( int x, int y, int x1, int y1 ), void( __thiscall* )( void*, int, int, int, int ), ctx::mem.ISurface.SetClipRect )( x, y, x1, y1 );
	CUSTOM_VFUNC( DrawColoredCircle( int x, int y, float radius, int r, int g, int b, int a ), void( __thiscall* )( void*, int, int, float, int, int, int, int ), ctx::mem.ISurface.DrawColoredCircle )( x, y, radius, r, g, b, a );
	CUSTOM_VFUNC( DrawColoredText( HFont font, int x, int y, int r, int g, int b, int a, const char* txt ),
				  void( __thiscall* )( void*, HFont, int, int, int, int, int, int, const char*, const char* ), ctx::mem.ISurface.DrawColoredText )( font, x, y, r, g, b, a, txt, nullptr );

	CUSTOM_VFUNC( StartDrawing(), void( __thiscall* )( void* ), ctx::mem.ISurface.StartDrawing )( );
	CUSTOM_VFUNC( FinishDrawing(), void( __thiscall* )( void* ), ctx::mem.ISurface.FinishDrawing )( );

	OFFSET( bool, m_bClippingEnabled, ctx::mem.ISurface.m_bClippingEnabled );
};
