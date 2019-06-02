#pragma once

struct entity_t : public IClientEntity
{
	template< typename t = entity_t >
	static t * get( const int index )
	{
		return reinterpret_cast< t* >( ctx::csgo.entlist->GetClientEntity( index ) );
	}

	template< typename t = entity_t >
	static t * get( const CBaseHandle handle )
	{
		return reinterpret_cast< t* >( ctx::csgo.entlist->GetClientEntityFromHandle( handle ) );
	}

	template<typename t = uintptr_t>
	void write( ptrdiff_t offset, t in )
	{
		*reinterpret_cast< t* >( uintptr_t( this ) + offset ) = in;
	}

	template<typename t = uintptr_t>
	t read( ptrdiff_t offset )
	{
		return *reinterpret_cast< t* >( uintptr_t( this ) + offset );
	}

	NETVAR( int, get_team, "DT_BaseEntity", "m_iTeamNum" );
	NETVAR( math::vec3_t, get_origin, "DT_BaseEntity", "m_vecOrigin" );
	NETVAR( math::vec3_t, get_mins, "DT_BaseEntity", "m_vecMins" );
	NETVAR( math::vec3_t, get_maxs, "DT_BaseEntity", "m_vecMaxs" );
	NETVAR( float, get_simtime, "DT_BaseEntity", "m_flSimulationTime" );

	NETVARADD( math::matrix3x4_t, get_coord_frame, "DT_BaseEntity", "m_CollisionGroup", -0x30 );

	VFUNC( 17, get_pred_desc_map(), datamap_t * ( __thiscall* )( void* ) )( );

	CUSTOM_VFUNC( set_abs_origin( math::vec3_t origin ), void( __thiscall* )( void*, const math::vec3_t& ), ctx::mem.CBaseEntity.SetAbsOrigin )( origin );
	CUSTOM_VFUNC( set_abs_angles( math::angle_t origin ), void( __thiscall* )( void*, const math::angle_t& ), ctx::mem.CBaseEntity.SetAbsAngles )( origin );
	CUSTOM_VFUNC( think(), void( __thiscall* )( void* ), ctx::mem.CBaseEntity.Think )( );
	CUSTOM_VFUNC( should_collide( int collision_group, int contents_mask ), bool( __thiscall* )( void*, int, int ), ctx::mem.CBaseEntity.ShouldCollide )( collision_group, contents_mask );

	DATAMAPVAR( get_move_type, int, "m_MoveType" );

	player_info_t get_player_info();
	bool get_bbox( math::vec4_t& box );
};

struct animating_t : public entity_t
{
	NETVAR( int, get_hitbox_set, "DT_BaseAnimating", "m_nHitboxSet" );
};

struct econ_entity_t : public animating_t
{

};

struct weapon_t : public econ_entity_t
{
	NETVAR( short, get_definition_index, "DT_WeaponBaseItem", "m_iItemDefinitionIndex" );
	NETVAR( int, get_ammo, "DT_WeaponBaseItem", "m_iClip1" );
	NETVAR( CBaseHandle, get_owner, "DT_BaseCombatWeapon", "m_hOwner" );

	CUSTOM_VFUNC( get_wpn_data(), CCSWeaponData* ( __thiscall* )( void* ), ctx::mem.CWeaponCSBase.GetCSWpnData )( );
	CUSTOM_VFUNC( get_inaccuracy(), float( __thiscall* )( void* ), ctx::mem.CWeaponCSBase.GetInaccuracy )( );
	CUSTOM_VFUNC( update_accuracy(), void( __thiscall* )( void* ), ctx::mem.CWeaponCSBase.UpdateAccuracy )( );
};

struct combat_character_t : public animating_t
{
	NETVAR( float, get_next_attack, "DT_BaseCombatCharacter", "m_flNextAttack" );
};

struct player_t : public combat_character_t
{
	NETVAR( bool, has_helmet, "DT_CSPlayer", "m_bHasHelmet" );
	NETVAR( bool, is_scoped, "DT_CSPlayer", "m_bIsScoped" );
	NETVAR( bool, has_defuser, "DT_CSPlayer", "m_bHasDefuser" );
	NETVAR( bool, is_immune, "DT_CSPlayer", "m_bGunGameImmunity" );
	NETVAR( int, get_health, "DT_BasePlayer", "m_iHealth" );
	NETVAR( short, get_lifestate, "DT_BasePlayer", "m_lifeState" );
	NETVAR( CBaseHandle, get_weapon_handle, "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	NETVAR( math::vec3_t, get_velocity, "DT_BasePlayer", "m_vecVelocity[0]" );
	NETVAR( math::vec3_t, get_view_offset, "DT_BasePlayer", "m_vecViewOffset[0]" );
	NETVAR( math::vec3_t, get_punch_angle, "DT_BasePlayer", "m_aimPunchAngle" );
	NETVAR( bitflag_t, get_flags, "DT_BasePlayer", "m_fFlags" );
	NETVAR( float, get_health_boost_time, "DT_CSPlayer", "m_flHealthShotBoostExpirationTime" );

	DATAMAPVAR( get_water_level, char, "m_nWaterLevel" );

	CUSTOM_VFUNC( pre_think(), void( __thiscall* )( void* ), ctx::mem.CBasePlayer.PreThink )( );
	CUSTOM_VFUNC( post_think(), void( __thiscall* )( void* ), ctx::mem.CBasePlayer.PostThink )( );
	CUSTOM_VFUNC( update_animations(), void( __thiscall* )( void* ), ctx::mem.CCSPlayer.UpdateClientSideAnimations )( );
	CUSTOM_VFUNC( weapon_shootpos( math::vec3_t* in ), float* ( __thiscall* )( void*, math::vec3_t* ), ctx::mem.CCSPlayer.Weapon_Shootpos )( in );

	math::vec3_t get_eye_pos();

	bool is_alive();
	bool is_enemy();
};