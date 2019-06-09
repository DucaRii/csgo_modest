#pragma once
#include "../../context/mem.hpp"

struct CInputSystem
{
	CUSTOM_VFUNC( EnableInput( bool enable ), void( __thiscall* )( void*, bool ), ctx::mem.CInputSystem.EnableInput )( enable );
};