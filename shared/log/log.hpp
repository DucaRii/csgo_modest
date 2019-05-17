#pragma once

namespace shared::log
{
	void print( const char* text );
	void detach();
}

#define LOG( text ) shared::log::print( text )