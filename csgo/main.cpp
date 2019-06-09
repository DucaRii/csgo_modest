#include "csgo.hpp"

namespace ctx
{
	csgo_t csgo = csgo_t{};
	client_t client = client_t{};
	mem_t mem = mem_t{};
	cfg_t cfg = cfg_t{};
}

BOOL WINAPI detach()
{
	event_handler::undo();

	input::undo();

	hooks::undo();

	log::detach();

	return TRUE;
}

DWORD WINAPI entry( LPVOID lpThreadParameter )
{
	try
	{
		input::init( L"Valve001" );

		LOG( "Initialized Input!" );

		netvars::init();

		LOG( "Initialized Netvars!" );

		weaponids.init();

		LOG( "Initialized Weapon IDs!" );

		classids.init();

		LOG( "Initialized Class IDs!" );

		render::init();

		LOG( "Initialized Renderer!" );

		menu::init();

		LOG( "Initialized Menu!" );

		hooks::init();

		LOG( "Initialized Hooks!" );

		config::set_config_directory( "modest_cfg" );

		LOG( "Cheat Attached!" );

		while ( !input::get_key_info( VK_END ).m_state )
			std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
	}
	catch ( const std::runtime_error& err )
	{
		/// Error while initializing the cheat
		LOG( err.what() );

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}

	LOG( "Cheat Detached!" );

	std::this_thread::sleep_for( std::chrono::milliseconds( 400 ) );

	detach();

	FreeLibraryAndExitThread( static_cast< HMODULE >( lpThreadParameter ), EXIT_SUCCESS );
}

BOOL APIENTRY DllMain( _In_ HINSTANCE hinstDLL,
					   _In_ DWORD     fdwReason,
					   _In_ LPVOID    lpvReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hinstDLL );

		if ( auto handle = CreateThread( nullptr, NULL, entry, hinstDLL, NULL, nullptr ) )
		{
			CloseHandle( handle );
		}
	}
	else if ( fdwReason == DLL_PROCESS_DETACH &&
			  !lpvReserved )
	{
		return detach();
	}

	return TRUE;
}