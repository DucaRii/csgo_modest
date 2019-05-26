#pragma once

#include "../../context/mem.hpp"

struct IVEngineClient
{
	CUSTOM_VFUNC( GetScreenSize( int& w, int& h ), HFont( __thiscall* )( void*, int&, int& ), ctx::mem.IVEngineClient.GetScreenSize )( w, h );
	CUSTOM_VFUNC( GetPlayerInfo( int index, player_info_t* info ), void( __thiscall* )( void*, int, player_info_t* ), ctx::mem.IVEngineClient.GetPlayerInfo )( index, info );
	CUSTOM_VFUNC( GetPlayerForUserId( int id ), int32_t( __thiscall* )( void*, int ), ctx::mem.IVEngineClient.GetPlayerForUserId )( id );
	CUSTOM_VFUNC( GetLocalPlayer(), int32_t( __thiscall* )( void* ), ctx::mem.IVEngineClient.GetLocalPlayer )( );
	CUSTOM_VFUNC( GetViewAngles( math::angle_t& ang ), void( __thiscall* )( void*, math::angle_t& ), ctx::mem.IVEngineClient.GetViewAngles )( ang );
	CUSTOM_VFUNC( SetViewAngles( math::angle_t& ang ), void( __thiscall* )( void*, math::angle_t& ), ctx::mem.IVEngineClient.SetViewAngles )( ang );
	CUSTOM_VFUNC( IsInGame(), bool( __thiscall* )( void* ), ctx::mem.IVEngineClient.IsInGame )( );
	CUSTOM_VFUNC( IsConnected(), bool( __thiscall* )( void* ), ctx::mem.IVEngineClient.IsConnected )( );
	CUSTOM_VFUNC( WorldToScreenMatrix(), const math::view_matrix_t&( __thiscall* )( void* ), ctx::mem.IVEngineClient.WorldToScreenMatrix )( );
	CUSTOM_VFUNC( ClientCmd_Unrestricted( const char* cmd, const char* unk_flag = nullptr ), void( __thiscall* )( void*, const char*, const char* ), ctx::mem.IVEngineClient.ClientCmd_Unrestricted )( cmd, unk_flag );
};