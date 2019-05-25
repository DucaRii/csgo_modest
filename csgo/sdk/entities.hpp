#pragma once

struct entity_t : public IClientEntity
{

};

struct animating_t : public entity_t
{
	
};

struct econ_entity_t : public animating_t
{

};

struct weapon_t : public econ_entity_t
{

};

struct combat_character_t : public animating_t
{
	
};

struct player_t : public combat_character_t
{

};