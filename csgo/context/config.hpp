#pragma once

#define ADD_ITEM( type, name ) type name

namespace ctx
{
	struct config_t
	{
		ADD_ITEM( bool, bhop ) = false;
		ADD_ITEM( bool, name_esp ) = false;
		ADD_ITEM( bool, health_esp ) = false;
	};

	extern config_t config;
}