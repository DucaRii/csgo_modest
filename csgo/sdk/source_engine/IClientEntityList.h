#pragma once

#include "../../context/mem.hpp"

struct entity_t;

struct IClientEntityList
{
	CUSTOM_VFUNC( GetClientEntity( int index ), entity_t* ( __thiscall* )( void*, int ), ctx::mem.IClientEntityList.GetClientEntity )( index );
	CUSTOM_VFUNC( GetClientEntityFromHandle( CBaseHandle handle ), entity_t* ( __thiscall* )( void*, CBaseHandle ), ctx::mem.IClientEntityList.GetClientEntityFromHandle )( handle );

	VFUNC( 6, GetHighestEntityIndex(), int( __thiscall* )( void* ) )( );
};