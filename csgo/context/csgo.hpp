#pragma once

#define ADD_INTERFACE( type, var_name, mod, interface_name ) __declspec( noinline ) type* var_name() \
{ \
	static type* ptr = nullptr; \
	if( !ptr ) ptr = reinterpret_cast<type*>( interface_handler::get( mod, interface_name ) ); \
	return ptr; \
} \

namespace ctx
{
	struct csgo_t
	{
		ADD_INTERFACE( ISurface, surface, "vguimatsurface.dll", "VGUI_Surface" );
	};

	extern csgo_t csgo;
}