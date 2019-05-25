#pragma once

struct IServer
{
	VFUNC( 10, GetAllClasses(), ServerClass* ( __thiscall* )( void* ) )( );
};