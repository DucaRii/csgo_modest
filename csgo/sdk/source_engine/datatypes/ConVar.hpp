#pragma once

#include "../../../context/mem.hpp"

struct ConVar
{
	VFUNC( 14, SetValue( const char* value ), void( __thiscall* )( void*, const char* ) )( value );
	VFUNC( 15, SetValue( float value ), void( __thiscall* )( void*, float ) )( value );
	VFUNC( 16, SetValue( int value ), void( __thiscall* )( void*, int ) )( value );
	VFUNC( 16, SetValue( bool value ), void( __thiscall* )( void*, int ) )( static_cast< int >( value ) );
};