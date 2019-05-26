#pragma once

struct player_t;
struct entity_t;

namespace game
{
	CCStrike15ItemSystem* get_item_system();
	CCStrike15ItemSchema* get_item_schema();

	bool world_to_screen( const math::vec3_t& origin, math::vec3_t& screen );

	enum e_player_iteration_flags
	{
		ALLOW_DEAD = 1 << 0,
		ENEMY_ONLY = 1 << 1,
		ALLOW_DORMANT = 1 << 2
	};
	void for_every_player( const std::function<bool( player_t* pl )>& func, bitflag_t flags = {} );

	enum e_entity_iteration_flags
	{
		FILTER_CLASSID = 1 << 0
	};
	void for_every_entity( const std::function<void( entity_t* ent )>& func, bitflag_t flags = {}, int classid = 0 );
}