#pragma once

#include "../../context/mem.hpp"

struct CEconItemDefinition
{
	char pad_0x0000[ 0x8 ]; ///0x0000
	int32_t m_iItemDefinitionIndex; ///0x0008 
	char pad_0x000C[ 0x40 ]; ///0x000C
	char* m_szHudName; ///0x004C 
	char pad_0x0050[ 0x4 ]; ///0x0050
	char* m_szWeaponType; ///0x0054 
	char pad_0x0058[ 0x4 ]; ///0x0058
	char* m_szWeaponDescription; ///0x005C 
	char pad_0x0060[ 0x34 ]; ///0x0060
	char* m_szViewModel; ///0x0094 
	char pad_0x0098[ 0x4 ]; ///0x0098
	char* m_szWorldModel; ///0x009C 
	char* m_szWorldModelDropped; ///0x00A0 
	char pad_0x00A4[ 0x110 ]; ///0x00A4
	char* m_szWeaponName1; ///0x01B4 
	char pad_0x01B8[ 0x8 ]; ///0x01B8
	char* m_szWeaponName; ///0x01C0 
	char pad_0x01C4[ 0x27C ]; ///0x01C4
}; ///Size=0x0440

struct CCStrike15ItemSchema
{
	VFUNC( 3, GetItemDefinitionCount(), int( __thiscall* )( void* ) )( );

	CUSTOM_VFUNC( GetItemDefinitionByName( const char* name ), CEconItemDefinition* ( __thiscall* )( void*, const char* ), ctx::mem.CItemSystem.GetItemDefinitionByName )( name );

	uintptr_t GetItemDefinitionMap()
	{
		return address_t( uintptr_t( this ) + ctx::mem.CItemSystem.m_Map ).get( 1 );
	}

	/// This is inlined on Windows so it needs to be rebuilt
	CEconItemDefinition* GetItemDefinitionByMapIndex( int i )
	{
		if ( i < 0 || i >= GetItemDefinitionCount() )
			return nullptr;

		///												  (v4 = 3 * v3, v5 = v2[0x35], *(v5 + 4 * v4 + 8) < -1) )
		return *reinterpret_cast< CEconItemDefinition * * >( GetItemDefinitionMap() + 0x4 * ( i * 0x3 ) + sizeof( void* ) );
	}
};

struct CCStrike15ItemSystem
{
	virtual CCStrike15ItemSchema* GetItemSchemaInterface() = 0;
};