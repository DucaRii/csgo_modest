#pragma once

struct CFontManager
{
	CUSTOM_VFUNC( CreateFont( int unk ), HFont( __thiscall* )( void*, int ), ctx::mem.CFontManager.CreateFont_ )( unk );
	CUSTOM_VFUNC( GetTextSize( HFont font, const wchar_t* text, int& w, int& h ), HFont( __thiscall* )( void*, HFont, const wchar_t*, int&, int& ), ctx::mem.CFontManager.GetTextSize )( font, text, w, h );
	CUSTOM_VFUNC( SetFontGlyphSet( HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0 ),
				  void( __thiscall* )( void*, HFont, const char*, int, int, int, int, int, signed int, signed int ), ctx::mem.CFontManager.SetFontGlyphSet )
				  ( font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax );
};