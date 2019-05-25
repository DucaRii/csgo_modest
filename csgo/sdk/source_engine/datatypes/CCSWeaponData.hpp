#pragma once

struct CCSWeaponData
{
	char pad_vtable[ 0x4 ]; // 0x0
	char* consoleName; // 0x4
	char pad_0[ 0xc ];// 0x8
	int32_t iMaxClip1; // 0x14
	int32_t iMaxClip2; // 0x18
	int32_t iDefaultClip1; // 0x1c
	int32_t iDefaultClip2; // 0x20
	int32_t iPrimaryReserveAmmoMax; // 0x24
	int32_t iSecondaryReserveAmmoMax; // 0x28
	char* szWorldModel; // 0x2c
	char* szViewModel; // 0x30
	char* szDroppedModel; // 0x34
	char pad_9[ 0x50 ];// 0x38
	char* szHudName; // 0x88
	char* szWeaponName; // 0x8c
	char pad_11[ 0x2 ];// 0x90
	bool bIsMeleeWeapon; // 0x92
	char pad_12[ 0x9 ];// 0x93
	float_t flWeaponWeight; // 0x9c
	char pad_13[ 0x2c ];// 0xa0
	int32_t iWeaponType; // 0xcc
	int32_t iWeaponPrice; // 0xd0
	int32_t iKillAward; // 0xd4
	char pad_16[ 0x4 ];// 0xd8
	float_t flCycleTime; // 0xdc
	float_t flCycleTimeAlt; // 0xe0
	char pad_18[ 0x8 ];// 0xe4
	bool bFullAuto; // 0xec
	char pad_19[ 0x3 ];// 0xed
	int32_t iDamage; // 0xf0
	float_t flArmorRatio; // 0xf4
	int32_t iBullets; // 0xf8
	float_t flPenetration; // 0xfc
	char pad_23[ 0x8 ];// 0x100
	float_t flWeaponRange; // 0x108
	float_t flRangeModifier; // 0x10c
	float_t flThrowVelocity; // 0x110
	char pad_26[ 0xc ];// 0x114
	bool bHasSilencer; // 0x120
	char pad_27[ 0xb ];// 0x121
	char* szBulletType; // 0x12c
	float_t flMaxSpeed; // 0x130
	char pad_29[ 0x50 ];// 0x134
	int32_t iRecoilSeed; // 0x184
};