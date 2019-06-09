#pragma once

#define ADD_INTERFACE( type, var_name, interface_name ) type* var_name = reinterpret_cast< type* >( interfaces::get( interface_name ) );

#define ADD_INTERFACE_MOD( type, var_name, mod, interface_name ) type* var_name = reinterpret_cast< type* >( interfaces::get( mod, interface_name ) );

#define ADD_INTERFACE_CUSTOM( type, var_name, address ) type* var_name = address.cast< type* >();

namespace ctx
{
	struct csgo_t
	{
		ADD_INTERFACE_MOD( ISurface, surface, "vguimatsurface.dll", "VGUI_Surface" );
		ADD_INTERFACE( IVEngineClient, engine, "VEngineClient0" );
		ADD_INTERFACE( IVEngineVGui, enginevgui, "VEngineVGui" );
		ADD_INTERFACE( ICVar, cvar, "VEngineCvar" );
		ADD_INTERFACE( CHLClient, client, "VClient0" );
		ADD_INTERFACE( IServer, server, "ServerGameDLL0" );
		ADD_INTERFACE( IClientEntityList, entlist, "VClientEntityList" );
		ADD_INTERFACE( ISchemeManager, scheme_manager, "VGUI_Scheme" );
		ADD_INTERFACE( IGameEventManager2, events, "GAMEEVENTSMANAGER002" );
		ADD_INTERFACE( CInputSystem, inputsys, "InputSystemVersion0" );

		ADD_INTERFACE_CUSTOM( CFontManager, font_manager, mem::find_ida_sig( "vguimatsurface.dll", { "74 1D 8B 0D ? ? ? ? 68 ? ? ? ?" } ).self_offset( 0x4 ).self_get() );
		ADD_INTERFACE_CUSTOM( IClientMode, clientmode, mem::get_vfunc( this->client, 10 ).self_find_opcode( 0x0D, 0x1 ).self_get( 2 ) );
		ADD_INTERFACE_CUSTOM( CGlobalVarsBase, globals, mem::get_vfunc( this->client, 0 ).self_find_opcode( 0xA3, 0xB ).self_get( 2 ) );
	};

	extern csgo_t csgo;
}