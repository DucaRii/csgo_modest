#include "../csgo.hpp"

player_info_t entity_t::get_player_info()
{
	if ( !this )
		return {};

	player_info_t info;
	ctx::csgo.engine->GetPlayerInfo( this->EntIndex(), &info );
	return info;
}

shared::math::vec3_t player_t::get_eye_pos()
{
	auto pos = shared::math::vec3_t{};

	weapon_shootpos( &pos );

	return pos;
}

bool player_t::is_alive()
{
	return get_lifestate() == ALIVE;
}

bool player_t::is_enemy()
{
	if ( !ctx::client.local )
		return false;

	return ctx::client.local->get_team() != this->get_team();
}
