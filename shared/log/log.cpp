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
			auto is_console_attached = AttachConsole( GetCurrentProcessId() );

			/// Redirect out/in to console
			freopen_s( reinterpret_cast< FILE * * >( stdin ), "CONIN$", "r", stdin );
			freopen_s( reinterpret_cast< FILE * * >( stdout ), "CONOUT$", "w", stdout );

			SetConsoleTitleA( "csgo_modest console" );

			m_init = is_console_allocated && is_console_attached;
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
		fclose( stdin );

		/// Now close the actual console
		FreeConsole();
		PostMessageW( GetConsoleWindow(), WM_CLOSE, 0, 0 );
	}
}