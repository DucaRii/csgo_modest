#pragma once

struct player_info_t
{
	int64_t __pad0;
	union
	{
		int64_t xuid;
		struct
		{
			int xuidlow;
			int xuidhigh;
		};
	};
	char name[ 128 ];
	int userid;
	char guid[ 33 ];
	unsigned int friendsid;
	char friendsname[ 128 ];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[ 4 ];
	unsigned char filesdownloaded;
};