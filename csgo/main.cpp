#include "csgo.hpp"

DWORD WINAPI entry( LPVOID lpThreadParameter )
{
DETACH:
	FreeLibraryAndExitThread( static_cast< HMODULE >( lpThreadParameter ), NULL );
}

BOOL WINAPI detach()
{
	return TRUE;
}

BOOL APIENTRY DllMain( _In_ HINSTANCE hinstDLL,
					   _In_ DWORD     fdwReason,
					   _In_ LPVOID    lpvReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		DisableThreadLibraryCalls( hinstDLL );
		CreateThread( nullptr, NULL, entry, nullptr, NULL, nullptr );
	}
	else if ( fdwReason == DLL_PROCESS_DETACH &&
			  !lpvReserved )
	{
		return detach();
	}

	return TRUE;
}