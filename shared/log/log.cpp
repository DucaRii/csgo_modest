#include "../shared.hpp"

#include "../fmt/chrono.hpp"

namespace shared::log
{
	bool m_init = false;

	void print( const char* text )
	{
		/// Check if console was allocated yet
		if ( !m_init )
		{
			/// Allocate console
			auto is_console_allocated = AllocConsole();

			FILE* m_file;
			/// Redirect stdout to console
			freopen_s( &m_file, "CONOUT$", "w", stdout );

			m_init = is_console_allocated && m_file;
		}

		/// Print text
		shared::fmt::print( "[{:%H:%M:%S}] - {} \n", fmt::localtime( std::time( nullptr ) ), text );
	}

	/// Wrapper for string objects
	void print( const std::string& text )
	{
		print( text.c_str() );
	}

	void detach()
	{
		/// Sanity check
		if ( !m_init )
			return;

		/// Close used handles first
		fclose( stdout );

		/// Now close the actual console
		FreeConsole();
		PostMessageW( GetConsoleWindow(), WM_CLOSE, 0, 0 );
	}
}
