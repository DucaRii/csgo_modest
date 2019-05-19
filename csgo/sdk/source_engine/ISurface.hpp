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
	CUSTOM_VFUNC( CreateFont(), HFont( __thiscall* )( void* ), ctx::mem.ISurface.CreateFont_ )( );
	CUSTOM_VFUNC( GetFontTall( HFont font ), int( __thiscall* )( void*, HFont ), ctx::mem.ISurface.GetFontTall )( font );
	CUSTOM_VFUNC( GetCharacterWidth( HFont font, char ch ), int( __thiscall* )( void*, HFont, char ), ctx::mem.ISurface.GetCharacterWidth )( font, ch );
	CUSTOM_VFUNC( DrawColoredText( HFont font, int x, int y, int r, int g, int b, int a, const char* txt ),
				  void( __thiscall* )( void*, HFont, int, int, int, int, int, int, const char*, const char* ), ctx::mem.ISurface.DrawColoredText )( font, x, y, r, g, b, a, txt, nullptr );
};