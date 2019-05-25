#pragma once

namespace ctx
{
	struct client_t
	{
		player_t* local;
		CUserCmd* cmd;
	};

	extern client_t client;
}