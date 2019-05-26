#include "../../csgo.hpp"

namespace game
{
	CCStrike15ItemSystem* get_item_system()
	{
		static auto fn = ctx::mem.CItemSystem.Get.cast < CCStrike15ItemSystem * ( __stdcall* )( )>();
		return fn();
	}

	CCStrike15ItemSchema* get_item_schema()
	{
		return get_item_system()->GetItemSchemaInterface();
	}

	bool world_to_screen( const math::vec3_t& origin, math::vec3_t& screen )
	{
		const auto screen_transform = [ & ]( const math::vec3_t & in, math::vec3_t & out ) -> bool
		{
			const auto& w2_s_matrix = ctx::csgo.engine->WorldToScreenMatrix();
			out.x = w2_s_matrix[ 0 ][ 0 ] * in.x + w2_s_matrix[ 0 ][ 1 ] * in.y + w2_s_matrix[ 0 ][ 2 ] * in.z + w2_s_matrix[ 0 ][ 3 ];
			out.y = w2_s_matrix[ 1 ][ 0 ] * in.x + w2_s_matrix[ 1 ][ 1 ] * in.y + w2_s_matrix[ 1 ][ 2 ] * in.z + w2_s_matrix[ 1 ][ 3 ];
			out.z = 0.0f;

			const auto w = w2_s_matrix[ 3 ][ 0 ] * in.x + w2_s_matrix[ 3 ][ 1 ] * in.y + w2_s_matrix[ 3 ][ 2 ] * in.z + w2_s_matrix[ 3 ][ 3 ];

			if ( w < 0.001f )
			{
				out.x *= 100000;
				out.y *= 100000;
				return false;
			}

			const auto invw = 1.0f / w;
			out.x *= invw;
			out.y *= invw;

			return true;
		};

		if ( screen_transform( origin, screen ) )
		{
			math::vec2_t screen_size = render::get_screen_size();

			screen.x = ( screen_size.x / 2.0f ) + ( screen.x * screen_size.x ) / 2.0f;
			screen.y = ( screen_size.y / 2.0f ) - ( screen.y * screen_size.y ) / 2.0f;

			return true;
		}
		return false;
	}

	void for_every_player( const std::function<bool( player_t * pl )> & func, bitflag_t flags )
	{
		for ( auto i = 1; i <= ctx::csgo.globals->maxClients; i++ )
		{
			auto player = entity_t::get<player_t>( i );
			if ( !player )
				continue;

			if ( !flags.has_flag( ALLOW_DEAD ) &&
				 !player->is_alive() )
				continue;

			if ( flags.has_flag( ENEMY_ONLY ) &&
				 !player->is_enemy() )
				continue;

			if ( !flags.has_flag( ALLOW_DORMANT ) &&
				 player->IsDormant() )
				continue;

			if ( func( player ) )
				break;
		}
	}

	void for_every_entity( const std::function<void( entity_t * ent )> & func, bitflag_t flags, int classid )
	{
		for ( auto i = ctx::csgo.globals->maxClients + 1; i < ctx::csgo.entlist->GetHighestEntityIndex(); i++ )
		{
			auto entity = entity_t::get( i );
			if ( !entity )
				continue;

			if ( flags.has_flag( FILTER_CLASSID ) &&
				 classid != entity->GetClientClass()->m_ClassID )
				continue;

			func( entity );
		}
	}
}