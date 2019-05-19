#include "csgo.hpp"

namespace ctx
{
	csgo_t csgo = csgo_t{};
	client_t client = client_t{};
	mem_t mem = mem_t{};
	config_t config = config_t{};
}

BOOL WINAPI detach()
{
	shared::log::detach();

	return TRUE;
}

DWORD WINAPI entry( LPVOID lpThreadParameter )
{
	LOG( "Cheat Attached!" );

	MessageBoxA( NULL, std::to_string( uintptr_t( ctx::csgo.surface() ) ).c_str(), "gg", 0 );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

DETACH:
	LOG( "Cheat Detached!" );

	std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

	detach();

	FreeLibraryAndExitThread( static_cast< HMODULE >( lpThreadParameter ), 1 );
}

BOOL APIENTRY DllMain( _In_ HINSTANCE hinstDLL,
					   _In_ DWORD     fdwReason,
					   _In_ LPVOID    lpvReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hinstDLL );

		if ( auto handle = CreateThread( nullptr, NULL, entry, nullptr, NULL, nullptr ) )
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