#include "../../csgo.hpp"

weaponids_t weaponids = {};

#define GET_ID( var ) var = get( CT_HASH( #var ) );

void weaponids_t::init()
{
	GET_ID( weapon_deagle );
	GET_ID( weapon_elite );
	GET_ID( weapon_fiveseven );
	GET_ID( weapon_glock );
	GET_ID( weapon_ak47 );
	GET_ID( weapon_aug );
	GET_ID( weapon_awp );
	GET_ID( weapon_famas );
	GET_ID( weapon_g3sg1 );
	GET_ID( weapon_galilar );
	GET_ID( weapon_m249 );
	GET_ID( weapon_m4a1 );
	GET_ID( weapon_mac10 );
	GET_ID( weapon_p90 );
	GET_ID( weapon_mp5sd );
	GET_ID( weapon_ump45 );
	GET_ID( weapon_xm1014 );
	GET_ID( weapon_bizon );
	GET_ID( weapon_mag7 );
	GET_ID( weapon_negev );
	GET_ID( weapon_sawedoff );
	GET_ID( weapon_tec9 );
	GET_ID( weapon_taser );
	GET_ID( weapon_hkp2000 );
	GET_ID( weapon_mp7 );
	GET_ID( weapon_mp9 );
	GET_ID( weapon_nova );
	GET_ID( weapon_p250 );
	GET_ID( weapon_scar20 );
	GET_ID( weapon_sg556 );
	GET_ID( weapon_ssg08 );
	GET_ID( weapon_knifegg );
	GET_ID( weapon_knife );
	GET_ID( weapon_flashbang );
	GET_ID( weapon_hegrenade );
	GET_ID( weapon_smokegrenade );
	GET_ID( weapon_molotov );
	GET_ID( weapon_decoy );
	GET_ID( weapon_incgrenade );
	GET_ID( weapon_c4 );
	GET_ID( weapon_healthshot );
	GET_ID( weapon_knife_t );
	GET_ID( weapon_m4a1_silencer );
	GET_ID( weapon_usp_silencer );
	GET_ID( weapon_cz75a );
	GET_ID( weapon_revolver );
	GET_ID( weapon_tagrenade );
	GET_ID( weapon_fists );
	GET_ID( weapon_breachcharge );
	GET_ID( weapon_tablet );
	GET_ID( weapon_melee );
	GET_ID( weapon_axe );
	GET_ID( weapon_hammer );
	GET_ID( weapon_spanner );
	GET_ID( weapon_knife_ghost );
	GET_ID( weapon_firebomb );
	GET_ID( weapon_diversion );
	GET_ID( weapon_frag_grenade );
	GET_ID( weapon_snowball );
	GET_ID( weapon_bumpmine );
	GET_ID( weapon_bayonet );
	GET_ID( weapon_knife_flip );
	GET_ID( weapon_knife_gut );
	GET_ID( weapon_knife_karambit );
	GET_ID( weapon_knife_m9_bayonet );
	GET_ID( weapon_knife_tactical );
	GET_ID( weapon_knife_falchion );
	GET_ID( weapon_knife_survival_bowie );
	GET_ID( weapon_knife_butterfly );
	GET_ID( weapon_knife_push );
	GET_ID( weapon_knife_ursus );
	GET_ID( weapon_knife_gypsy_jackknife );
	GET_ID( weapon_knife_stiletto );
	GET_ID( weapon_knife_widowmaker );
	GET_ID( studded_bloodhound_gloves );
	GET_ID( t_gloves );
	GET_ID( ct_gloves );
	GET_ID( sporty_gloves );
	GET_ID( slick_gloves );
	GET_ID( leather_handwraps );
	GET_ID( motorcycle_gloves );
	GET_ID( specialist_gloves );
}

uint32_t weaponids_t::get( uint32_t name )
{
	if ( m_weaponids.empty() )
	{
		auto item_schema = game::get_item_schema();
		auto max_count = item_schema->GetItemDefinitionCount();

		for ( auto i = 0; i < max_count; i++ )
		{
			const auto item = item_schema->GetItemDefinitionByMapIndex( i );
			if ( !item )
				continue;

			m_weaponids[ HASH( item->m_szWeaponName ) ] = item->m_iItemDefinitionIndex;
		}
	}

	return m_weaponids[ name ];
}
