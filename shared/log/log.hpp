#pragma once

namespace shared::log
{
	/// <summary>
	/// Print given message into console with time in front of it
	/// </summary>
	/// <param name="text">Text which will be printed</param>
	void print( const char* text );

	/// <summary>
	/// Print given message into console with time in front of it
	/// </summary>
	/// <param name="text">Text which will be printed</param>
	void print( const std::string& text );

	/// <summary>
	/// Restores original handles and removes the console
	/// </summary>
	void detach();
}

#define LOG( text ) shared::log::print( text )