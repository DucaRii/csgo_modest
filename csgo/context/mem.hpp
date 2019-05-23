#pragma once

namespace ctx
{
	struct mem_t
	{
		struct ISurface_t
		{
			shared::address_t DrawSetColor = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 66 0F 6E 45 ? 8A 45 08" } ); /// 15
			shared::address_t DrawFilledRect = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 40 53 8B D9" } ); /// 16
			shared::address_t DrawOutlinedRect = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 51 56 8B F1 89 75 FC" } ); /// 18
			shared::address_t DrawLine = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 20 57" } ); /// 19
			shared::address_t DrawSetTexture = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 56 8B 75 08 57 8B F9 3B B7 ? ? ? ?" } ); /// 38
			shared::address_t IsTextureIDValid = shared::mem::find_ida_sig( "vguimatsurface.dll", { "B0 01 C2 04 00" } ); /// 42
			shared::address_t CreateNewTextureID = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC B9 ? ? ? ? A1 ? ? ? ? 5D FF 20" } ); /// 43
			shared::address_t GetFontTall = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 8B 45 08 8D 0C C5 ? ? ? ? 2B C8 A1 ? ? ? ? 83 7C 88 ? ? 8D 04 88" } ); /// 74
			shared::address_t GetCharacterWidth = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 8B 45 08 0F B7 55 0C" } ); /// 78
			shared::address_t DrawOutlinedCircle = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 50 57 8B F9 89 7D F0 80 7F 2F 00 0F 84 ? ? ? ? 8B 0D ? ? ? ? 53 8B 9F ? ? ? ? 56 8B 01 FF 90 ? ? ? ? 8B F0 85 F6 74 07 8B 06 8B CE FF 50 08 8B 06 8B CE 53 6A 00 6A 00 6A 01 FF 90 ? ? ? ? 89 47 3C 8B CE 8B 06 FF 50 0C 8B 06 8B CE FF 50 04 FF 75 14" } ); /// 103
			shared::address_t DrawTexturedPolygon = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 56 57 8B 7D 08 8B F1 85 FF 0F 84 ? ? ? ?" } ); /// 106
			shared::address_t DrawFilledRectFade = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 4C 53 57" } ); /// 123
			shared::address_t GetClipRect = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 B9 ? ? ? ? ? 74 39" } ); /// 146
			shared::address_t SetClipRect = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 56 8B F1 83 BE ? ? ? ? ? 74 7F" } ); /// 147
			shared::address_t DrawColoredCircle = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 0C 8A 45 14" } ); /// 163
			shared::address_t DrawColoredText = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 81 EC ? ? ? ? 56 57 FF 75 10" } ); /// 164 
			
			shared::address_t m_bClippingEnabled = shared::mem::find_ida_sig( "vguimatsurface.dll", { "83 B9 ? ? ? ? ? 74 39" } ).self_offset( 0x2 ).self_get();
		} ISurface;

		struct CFontManager_t
		{

			shared::address_t SetFontGlyphSet = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 08 8B 45 08 53" } ); /// unk
			shared::address_t GetTextSize = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 EC 18 83 7D 0C 00" } ); /// unk
			shared::address_t CreateFont_ = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 56 8B F1 57 8B 4E 0C 8B 56 04 8D 41 01 3B C2 7E 0B 2B CA 41 51 8B CE E8 ? ? ? ? FF 46 0C 8B 56 0C 8B 7D 08 2B D7 8B 0E 4A 89 4E 10 85 D2 7E 26 8D 04 FD ? ? ? ? 2B C7 8D 0C 81 8D 04 D5 ? ? ? ? 2B C2 C1 E0 02 50 51 8D 41 1C 50 E8 ? ? ? ? 83 C4 0C 8B 0E 8D 14 FD ? ? ? ? 2B D7 " } ); /// unk
		} CFontManager;

		struct IVEngineClient_t
		{
			shared::address_t GetScreenSize = shared::mem::find_ida_sig( "engine.dll", { "55 8B EC 8B 0D ? ? ? ? 56 8B 01" } ); /// 5
			shared::address_t GetPlayerInfo = shared::mem::find_ida_sig( "engine.dll", { "55 8B EC 83 E4 F8 8B 0D ? ? ? ? 83 EC 08" } ); /// 8
			shared::address_t GetPlayerForUserId = shared::mem::find_ida_sig( "engine.dll", { "55 8B EC 83 E4 F8 A1 ? ? ? ? 81 EC ? ? ? ? 83 B8 ? ? ? ? ?" } ); /// 9
			shared::address_t GetLocalPlayer = shared::mem::find_ida_sig( "engine.dll", { "A1 ? ? ? ? B9 ? ? ? ? FF 50 14 8B 04 85 ? ? ? ? 8B 80 ? ? ? ? 40 C3" } ); /// 12
			shared::address_t GetViewAngles = shared::mem::find_ida_sig( "engine.dll", { "55 8B EC A1 ? ? ? ? B9 ? ? ? ? FF 50 14 8B 4D 08" } ); /// 18
			shared::address_t SetViewAngles = shared::mem::find_ida_sig( "engine.dll", { "55 8B EC 83 E4 C0 83 EC 3C 56 8B 75 08 8B 06" } ); /// 19
			shared::address_t ClientCmd_Unrestricted = shared::mem::find_ida_sig( "engine.dll", { "55 8B EC 8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 0C A1 ? ? ? ? 35 ? ? ? ? EB 05 8B 01 FF 50 34 50" } ); /// 114
		} IVEngineClient;

		struct IVEngineVGui_t
		{
			shared::address_t StartDrawing = shared::mem::find_ida_sig( "vguimatsurface.dll", { "55 8B EC 83 E4 ? 83 EC ? 80 3D ? ? ? ? 00 56 57 8B F9" } ); /// unk
			shared::address_t FinishDrawing = shared::mem::find_ida_sig( "vguimatsurface.dll", { "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? 00 8B 01 FF 90" } ); /// unk
		} IVEngineVGui;
	};

	extern mem_t mem;
}