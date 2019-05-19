#pragma once

struct IPanel
{
	/// TODO: Find a way to get this dynamically
	VFUNC( 36, GetName( int vguiPanel ), const char* ( __thiscall* )( void*, int ) )( vguiPanel );
};