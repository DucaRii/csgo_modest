#pragma once

#define ADD_ITEM( type, name ) type name

namespace ctx
{
	struct config_t
	{
		ADD_ITEM( bool, bhop ) = false;
		ADD_ITEM( bool, name_esp ) = false;
		ADD_ITEM( bool, health_esp ) = false;
		ADD_ITEM( int, health_style ) = 0;
		ADD_ITEM( float, some_float ) = 50.f;
		ADD_ITEM( bool, hitmarker ) = true;
	};

	extern config_t config;
}