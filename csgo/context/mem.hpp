#pragma once

#define ADD_ADDRESS( name, mod_name, sig ) address_t name =  mem::find_ida_sig( mod_name, sig )

namespace ctx
{
	struct mem_t
	{
		struct ISurface_t
		{
			ADD_ADDRESS( DrawSetColor, "vguimatsurface.dll", { "55 8B EC 66 0F 6E 45 ? 8A 45 08" } ); /// 15
			ADD_ADDRESS( DrawFilledRect, "vguimatsurface.dll", { "55 8B EC 83 EC 40 53 8B D9" } ); /// 16
			ADD_ADDRESS( DrawOutlinedRect, "vguimatsurface.dll", { "55 8B EC 51 56 8B F1 89 75 FC" } ); /// 18
			ADD_ADDRESS( DrawLine, "vguimatsurface.dll", { "55 8B EC 83 EC 20 57" } ); /// 19
			ADD_ADDRESS( DrawSetTexture, "vguimatsurface.dll", { "55 8B EC 56 8B 75 08 57 8B F9 3B B7 ? ? ? ?" } ); /// 38
			ADD_ADDRESS( IsTextureIDValid, "vguimatsurface.dll", { "B0 01 C2 04 00" } ); /// 42
			ADD_ADDRESS( CreateNewTextureID, "vguimatsurface.dll", { "55 8B EC B9 ? ? ? ? A1 ? ? ? ? 5D FF 20" } ); /// 43
			ADD_ADDRESS( UnlockCursor, "vguimatsurface.dll", { "80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 80 3D ? ? ? ? ?" } ); /// 66
			ADD_ADDRESS( LockCursor, "vguimatsurface.dll", { "80 3D ? ? ? ? ? 8B 91 ? ? ? ? 8B 0D ? ? ? ? C6 05 ? ? ? ? ? 8B 01 74 0B FF 35 ? ? ? ? 52 FF 50 34 C3 6A 00 52 FF 50 34 C3 55" } ); /// 67
			ADD_ADDRESS( CreateFont_, "vguimatsurface.dll", { "FF 35 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? C3" } ); /// 71
			ADD_ADDRESS( GetFontTall, "vguimatsurface.dll", { "55 8B EC 8B 45 08 8D 0C C5 ? ? ? ? 2B C8 A1 ? ? ? ? 83 7C 88 ? ? 8D 04 88" } ); /// 74
			ADD_ADDRESS( GetCharacterWidth, "vguimatsurface.dll", { "55 8B EC 8B 45 08 0F B7 55 0C" } ); /// 78
			ADD_ADDRESS( DrawOutlinedCircle, "vguimatsurface.dll", { "55 8B EC 83 EC 50 57 8B F9 89 7D F0 80 7F 2F 00 0F 84 ? ? ? ? 8B 0D ? ? ? ? 53 8B 9F ? ? ? ? 56 8B 01 FF 90 ? ? ? ? 8B F0 85 F6 74 07 8B 06 8B CE FF 50 08 8B 06 8B CE 53 6A 00 6A 00 6A 01 FF 90 ? ? ? ? 89 47 3C 8B CE 8B 06 FF 50 0C 8B 06 8B CE FF 50 04 FF 75 14" } ); /// 103
			ADD_ADDRESS( DrawTexturedPolygon, "vguimatsurface.dll", { "55 8B EC 56 57 8B 7D 08 8B F1 85 FF 0F 84 ? ? ? ?" } ); /// 106
			ADD_ADDRESS( DrawFilledRectFade, "vguimatsurface.dll", { "55 8B EC 83 EC 4C 53 57" } ); /// 123
			ADD_ADDRESS( GetClipRect, "vguimatsurface.dll", { "55 8B EC 83 B9 ? ? ? ? ? 74 39" } ); /// 146
			ADD_ADDRESS( SetClipRect, "vguimatsurface.dll", { "55 8B EC 56 8B F1 83 BE ? ? ? ? ? 74 7F" } ); /// 147
			ADD_ADDRESS( DrawColoredCircle, "vguimatsurface.dll", { "55 8B EC 83 EC 0C 8A 45 14" } ); /// 163
			ADD_ADDRESS( DrawColoredText, "vguimatsurface.dll", { "55 8B EC 81 EC ? ? ? ? 56 57 FF 75 10" } ); /// 164 

			ADD_ADDRESS( StartDrawing, "vguimatsurface.dll", { "55 8B EC 83 E4 ? 83 EC ? 80 3D ? ? ? ? 00 56 57 8B F9" } ); /// unk
			ADD_ADDRESS( FinishDrawing, "vguimatsurface.dll", { "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? 00 8B 01 FF 90" } ); /// unk

			ADD_ADDRESS( m_bClippingEnabled, "vguimatsurface.dll", { "83 B9 ? ? ? ? ? 74 39" } ).self_offset( 0x2 ).self_get();
		} ISurface;

		struct CFontManager_t
		{

			ADD_ADDRESS( SetFontGlyphSet, "vguimatsurface.dll", { "55 8B EC 83 EC 08 8B 45 08 53" } ); /// unk
			ADD_ADDRESS( GetTextSize, "vguimatsurface.dll", { "55 8B EC 83 EC 18 83 7D 0C 00" } ); /// unk
			ADD_ADDRESS( CreateFont_, "vguimatsurface.dll", { "55 8B EC 56 8B F1 57 8B 4E 0C 8B 56 04 8D 41 01 3B C2 7E 0B 2B CA 41 51 8B CE E8 ? ? ? ? FF 46 0C 8B 56 0C 8B 7D 08 2B D7 8B 0E 4A 89 4E 10 85 D2 7E 26 8D 04 FD ? ? ? ? 2B C7 8D 0C 81 8D 04 D5 ? ? ? ? 2B C2 C1 E0 02 50 51 8D 41 1C 50 E8 ? ? ? ? 83 C4 0C 8B 0E 8D 14 FD ? ? ? ? 2B D7 " } ); /// unk
		} CFontManager;

		struct IVEngineClient_t
		{
			ADD_ADDRESS( GetScreenSize, "engine.dll", { "55 8B EC 8B 0D ? ? ? ? 56 8B 01" } ); /// 5
			ADD_ADDRESS( GetPlayerInfo, "engine.dll", { "55 8B EC 83 E4 F8 8B 0D ? ? ? ? 83 EC 08" } ); /// 8
			ADD_ADDRESS( GetPlayerForUserId, "engine.dll", { "55 8B EC 83 E4 F8 A1 ? ? ? ? 81 EC ? ? ? ? 83 B8 ? ? ? ? ?" } ); /// 9
			ADD_ADDRESS( GetLocalPlayer, "engine.dll", { "A1 ? ? ? ? B9 ? ? ? ? FF 50 14 8B 04 85 ? ? ? ? 8B 80 ? ? ? ? 40 C3" } ); /// 12
			ADD_ADDRESS( GetViewAngles, "engine.dll", { "55 8B EC A1 ? ? ? ? B9 ? ? ? ? FF 50 14 8B 4D 08" } ); /// 18
			ADD_ADDRESS( SetViewAngles, "engine.dll", { "55 8B EC 83 E4 C0 83 EC 3C 56 8B 75 08 8B 06" } ); /// 19
			ADD_ADDRESS( IsInGame, "engine.dll", { "A1 ? ? ? ? 83 B8 ? ? ? ? ? 0F 94 C0 C3 A0 ? ? ? ?" } ); /// 26
			ADD_ADDRESS( IsConnected, "engine.dll", { "A1 ? ? ? ? 83 B8 ? ? ? ? ? 0F 9D C0 C3 55" } ); /// 27
			ADD_ADDRESS( WorldToScreenMatrix, "engine.dll", { "B9 ? ? ? ? A1 ? ? ? ? FF 60 38" } ); /// 37
			ADD_ADDRESS( ClientCmd_Unrestricted, "engine.dll", { "55 8B EC 8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 0C A1 ? ? ? ? 35 ? ? ? ? EB 05 8B 01 FF 50 34 50" } ); /// 114
		} IVEngineClient;

		struct ICVar_t
		{
			ADD_ADDRESS( FindVar, "vstdlib.dll", { "55 8B EC 8B 01 56 FF 75 08 FF 50 38 8B F0 85 F6 74 1E" } ); /// 16
		} ICVar;

		struct IClientEntityList_t
		{
			ADD_ADDRESS( GetClientEntity, "client_panorama.dll", { "55 8B EC 8B 45 08 85 C0 78 17 05 ? ? ? ?" } ); /// 3
			ADD_ADDRESS( GetClientEntityFromHandle, "client_panorama.dll", { "55 8B EC 8B 45 08 51 8B D4 89 02 8B 01 FF 50 08 8B C8 85 C9 74 09 8B 01 FF 50 18" } ); /// 4
		} IClientEntityList;

		struct CItemSystem_t
		{
			ADD_ADDRESS( Get, "client_panorama.dll", { "A1 ? ? ? ? 85 C0 75 53 A1 ? ? ? ? 56 68 ? ? ? ? 8B 08" } );

			ADD_ADDRESS( GetItemDefinitionByName, "client_panorama.dll", { "55 8B EC 57 8B F9 80 BF ? ? ? ? ? 74 07" } ); /// 42

			ADD_ADDRESS( m_Map, "client_panorama.dll", { "8B 87 ? ? ? ? 83 7C 88 ? ? 7C 0A 8B 44 88 04 5F 5E 5D C2 04 00 8B 87 ? ? ? ?" } ).self_offset( 0x2 ).self_get( 1 ).self_offset( -0x4 );
		} CItemSystem;

		struct CBaseEntity_t
		{
			ADD_ADDRESS( SetAbsOrigin, "client_panorama.dll", { "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8 ? ?" } );
			ADD_ADDRESS( SetAbsAngles, "client_panorama.dll", { "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8 ?" } );
			ADD_ADDRESS( Think, "client_panorama.dll", { "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8 ?" } );
			ADD_ADDRESS( ShouldCollide, "client_panorama.dll", { "55 8B EC 83 B9 ? ? ? ? ? 75 0F" } );
		} CBaseEntity;

		struct CBasePlayer_t
		{
			ADD_ADDRESS( PreThink, "client_panorama.dll", { "55 8B EC 83 E4 F8 51 56 8B F1 8B 06" } );
			ADD_ADDRESS( PostThink, "client_panorama.dll", { "56 8B 35 ? ? ? ? 57 8B F9 8B CE 8B 06 FF 90 ? ? ? ? 8B 07" } );
		} CBasePlayer;

		struct CCSPlayer_t
		{
			ADD_ADDRESS( m_pVtable, "client_panorama.dll", { "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 89 7C 24 0C" } ).self_offset( 0x45 ).offset( 0x2 );

			ADD_ADDRESS( UpdateClientSideAnimations, "client_panorama.dll", { "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" } );
			ADD_ADDRESS( Weapon_Shootpos, "client_panorama.dll", { "55 8B EC 56 8B 75 08 57 8B F9 56 8B 07 FF 90 ? ? ? ?" } );
		} CCSPlayer;

		struct CWeaponCSBase_t
		{
			ADD_ADDRESS( GetInaccuracy, "client_panorama.dll", { "55 8B EC 83 E4 F8 83 EC 10 56 8B F1 57 8B 96 ? ? ? ? 83 FA FF 74 25 0F B7 C2 C1 E0 04 05 ? ? ? ? C1 EA 10 39 50 04 75 12 8B 08 85 C9 74 0C 8B 01 8B 80 ? ? ? ? FF D0 EB 02 33 C0 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 50 E8 ? ? ? ? 8B F8 83 C4 14 85 FF 75 08" } );
			ADD_ADDRESS( UpdateAccuracy, "client_panorama.dll", { "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 8B 8F ? ? ? ?" } ); 
			ADD_ADDRESS( GetCSWpnData, "client_panorama.dll", { "55 8B EC 81 EC ?? ?? ?? ?? 53 8B D9 56 57 8D 8B ?? ?? ?? ?? 85 C9 75 04 33 FF EB 2F" } );
		} CWeaponCSBase;

		struct CInputSystem_t
		{
			address_t EnableInput = mem::find_ida_sig( "inputsystem.dll", { "55 8B EC 8A 45 08 88 81 ? ? ? ? 5D C2 04 00 55 8B EC 8A 45 08" } ); /// 11
		} CInputSystem;

		/// Unused, but works
		/*struct CGlobalVarsBase_t
		{
			byte curtime_offset = mem::find_ida_sig( "client_panorama.dll", { "8B 40 ? 89 86 ? ? ? ? E8 ? ? ? ? 80 BE ? ? ? ? ? 74 48" } ).self_offset( 0x2 ).self_get( 1 ).cast<byte>(); /// 0x10
			byte frametime_offset = mem::find_ida_sig( "client_panorama.dll", { "F3 0F 10 40 ? 0F 2F C1 76 06" } ).self_offset( 0x4 ).self_get( 1 ).cast<byte>(); /// 0x14
			byte ipt_offset = mem::find_ida_sig( "client_panorama.dll", { "	F3 0F 10 43 ? F3 0F 11 43 ? A1 ? ? ? ?" } ).self_offset( 0x4 ).self_get( 1 ).cast<byte>(); /// 0x20
		} CGlobalVarsBase;*/
	};

	extern mem_t mem;
}