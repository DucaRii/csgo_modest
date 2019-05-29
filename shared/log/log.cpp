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
			try
			{
				/// Allocate console
				if ( !AllocConsole() )
					throw std::runtime_error( "Failed to allocate console" );

				/// Attach console to desired process
				if ( !AttachConsole( GetCurrentProcessId() ) )
					throw std::runtime_error( "Failed to attach console" );

				/// Redirect stdin into console
				if ( freopen_s( reinterpret_cast< FILE * * >( stdin ), "CONIN$", "r", stdin ) )
					throw std::runtime_error( "Failed to redirect stdin" );

				/// Redirect stdout into console
				if ( freopen_s( reinterpret_cast< FILE * * >( stdout ), "CONIN$", "r", stdout ) )
					throw std::runtime_error( "Failed to redirect stdout" );

				/// Set console title
				if ( !SetConsoleTitleW( L"csgo_modest console" ) )
					throw std::runtime_error( "Failed to set title of console" );

				/// Everything went good! 
				m_init = true;
			}
			catch ( const std::runtime_error& err )
			{
				LOG( err.what() );

				/// Let's try that again next time :)
				m_init = false;
			}
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