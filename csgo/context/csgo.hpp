#pragma once

#define ADD_INTERFACE( type, var_name, mod, interface_name ) type* var_name = reinterpret_cast< type* >( interface_handler::get( mod, interface_name ) );

#define ADD_INTERFACE_CUSTOM( type, var_name, address ) type* var_name = address.cast< type* >();


namespace ctx
{
	struct csgo_t
	{
		ADD_INTERFACE( ISurface, surface, "vguimatsurface.dll", "VGUI_Surface" );
		ADD_INTERFACE( IPanel, panel, "vgui2.dll", "VGUI_Panel" );
		ADD_INTERFACE( IVEngineClient, engine, "engine.dll", "VEngineClient" );

		ADD_INTERFACE_CUSTOM( CFontManager, font_manager, shared::mem::find_ida_sig( "vguimatsurface.dll", { "74 1D 8B 0D ? ? ? ? 68 ? ? ? ?" } ).self_offset( 0x4 ).self_get() );
	};

	extern csgo_t csgo;
}