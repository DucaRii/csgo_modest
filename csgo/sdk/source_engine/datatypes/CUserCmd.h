#pragma once

enum
{
	IN_ATTACK = ( 1 << 0 ),
	IN_JUMP = ( 1 << 1 ),
	IN_DUCK = ( 1 << 2 ),
	IN_FORWARD = ( 1 << 3 ),
	IN_BACK = ( 1 << 4 ),
	IN_USE = ( 1 << 5 ),
	IN_CANCEL = ( 1 << 6 ),
	IN_LEFT = ( 1 << 7 ),
	IN_RIGHT = ( 1 << 8 ),
	IN_MOVELEFT = ( 1 << 9 ),
	IN_MOVERIGHT = ( 1 << 10 ),
	IN_ATTACK2 = ( 1 << 11 ),
	IN_RUN = ( 1 << 12 ),
	IN_RELOAD = ( 1 << 13 ),
	IN_ALT1 = ( 1 << 14 ),
	IN_ALT2 = ( 1 << 15 ),
	IN_SCORE = ( 1 << 16 ),
	IN_SPEED = ( 1 << 17 ),
	IN_WALK = ( 1 << 18 ),
	IN_ZOOM = ( 1 << 19 ),
	IN_WEAPON1 = ( 1 << 20 ),
	IN_WEAPON2 = ( 1 << 21 ),
	IN_BULLRUSH = ( 1 << 22 ),
	IN_GRENADE1 = ( 1 << 23 ),
	IN_GRENADE2 = ( 1 << 24 ),
	IN_ATTACK3 = ( 1 << 25 ),
};

enum
{
	MOVETYPE_NONE = 0,
	// never moves
	MOVETYPE_ISOMETRIC,
	// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,
	// player only - moving on the ground
	MOVETYPE_STEP,
	// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,
	// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,
	// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,
	// uses VPHYSICS for simulation
	MOVETYPE_PUSH,
	// no clip to world, push and crush
	MOVETYPE_NOCLIP,
	// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,
	// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,
	// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,
	// Allows the entity to describe its own physics
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	// should always be defined as the last item in the list
	MOVETYPE_MAX_BITS = 4
};

struct CUserCmd
{
	char pad_vtable[ 0x4 ];
	// For matching server and client commands for debugging
	int		command_number;

	// the tick the client created this command
	int		tick_count;

	// Player instantaneous view angles.
	math::angle_t	viewangles;

	math::vec3_t	aim_direction;
	// Intended velocities
	//	forward velocity.
	float	forwardmove;
	//  sideways velocity.
	float	sidemove;
	//  upward velocity.
	float	upmove;
	// Attack button states
	bitflag_t		buttons;
	// Impulse command issued.
	byte    impulse;
	// Current weapon id
	int		weaponselect;
	int		weaponsubtype;

	int		random_seed;	// For shared random functions

	short	mousedx;		// mouse accum in x from create move
	short	mousedy;		// mouse accum in y from create move

	// Client only, tracks whether we've predicted this command at least once
	bool	hasbeenpredicted;

	char    pad_0x4C[ 0x18 ];
};