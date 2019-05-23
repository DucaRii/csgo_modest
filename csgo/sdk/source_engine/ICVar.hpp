#pragma once

#include "../../context/mem.hpp"

struct ICVar
{
	CUSTOM_VFUNC( FindVar( const char* name ), ConVar*( __thiscall* )( void*, const char* ), ctx::mem.ICVar.FindVar )( name );
};