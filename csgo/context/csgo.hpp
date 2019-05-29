#pragma once

#define ADD_INTERFACE( type, var_name, mod, interface_name ) type* var_name = reinterpret_cast< type* >( interfaces::get( mod, interface_name ) );

#define ADD_INTERFACE_CUSTOM( type, var_name, address ) type* var_name = address.cast< type* >();

namespace ctx
{
	struct csgo_t
	{
		ADD_INTERFACE( ISurface, surface, "vguimatsurface.dll", "VGUI_Surface" );
		ADD_INTERFACE( IVEngineClient, engine, "engine.dll", "VEngineClient0" );
		ADD_INTERFACE( IVEngineVGui, enginevgui, "engine.dll", "VEngineVGui" );
		ADD_INTERFACE( ICVar, cvar, "vstdlib.dll", "VEngineCvar" );
		ADD_INTERFACE( CHLClient, client, "client_panorama.dll", "VClient0" );
		ADD_INTERFACE( IServer, server, "server.dll", "ServerGameDLL0" );
		ADD_INTERFACE( IClientEntityList, entlist, "client_panorama.dll", "VClientEntityList" );
		ADD_INTERFACE( ISchemeManager, scheme_manager, "vgui2.dll", "VGUI_Scheme" );

		ADD_INTERFACE_CUSTOM( CFontManager, font_manager, mem::find_ida_sig( "vguimatsurface.dll", { "74 1D 8B 0D ? ? ? ? 68 ? ? ? ?" } ).self_offset( 0x4 ).self_get() );
		ADD_INTERFACE_CUSTOM( IClientMode, clientmode, mem::get_vfunc( client, 10 ).self_find_opcode( 0x0D, 0x1 ).self_get( 2 ) );
		ADD_INTERFACE_CUSTOM( CGlobalVarsBase, globals, mem::get_vfunc( client, 0 ).self_find_opcode( 0xA3, 0xB ).self_get( 2 ) );
	};

	extern csgo_t csgo;
}