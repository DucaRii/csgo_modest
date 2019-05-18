#pragma once

namespace shared::log
{
	void print( const char* text );
	void print( const std::string& text );

	void detach();
}

#define LOG( text ) shared::log::print( text )