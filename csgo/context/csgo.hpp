#pragma once

#define ADD_INTERFACE( type, var_name, mod, interface_name ) __declspec( noinline ) type* var_name() \
{ \
	static type* ptr = nullptr; \
	if( !ptr ) ptr = reinterpret_cast<type*>( interface_handler::get( mod, interface_name ) ); \
	return ptr; \
} \

#define ADD_INTERFACE_CUSTOM( type, var_name, address ) __declspec( noinline ) type* var_name() \
{ \
	static type* ptr = nullptr; \
	if( !ptr ) ptr = address.as<type*>(); \
	return ptr; \
} \


namespace ctx
{
	struct csgo_t
	{
		ADD_INTERFACE( ISurface, surface, "vguimatsurface.dll", "VGUI_Surface" );
		ADD_INTERFACE( IPanel, panel, "vgui2.dll", "VGUI_Panel" );
		ADD_INTERFACE( IVEngineClient, engine, "engine.dll", "VEngineClient" );

		ADD_INTERFACE_CUSTOM( CFontManager, font_manager, shared::mem::find_ida_sig( "vguimatsurface.dll", { "74 1D 8B 0D ? ? ? ? 68 ? ? ? ?" } ).offset( 0x4 ).get() );
	};

	extern csgo_t csgo;
}