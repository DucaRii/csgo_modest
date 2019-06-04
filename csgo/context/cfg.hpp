#pragma once

namespace ctx
{
	struct cfg_t
	{
		/// MOVEMENT
		ADD_CFG_ITEM( bool, movement_bhop, false );

		/// PLAYER ESP
		ADD_CFG_ITEM( bool, playeresp_name, false );
		ADD_CFG_ITEM( bool, playeresp_health, false );
		ADD_CFG_ITEM( bool, playeresp_box, false );
		ADD_CFG_ITEM( int, playeresp_health_style, 0 );

		ADD_CFG_ITEM_VEC( std::vector<int>, int, 64, example_vector, 0 );
		ADD_CFG_ITEM_VEC( std::vector<bool>, bool, 16, example_vector_bool, true );
		ADD_CFG_ITEM_VEC( std::vector<float>, float, 22, example_vector_float, 5.f );

		/// MISC
		ADD_CFG_ITEM( bool, misc_hitmarker, true );

		/// DEBUG
		ADD_CFG_ITEM( float, some_float, 50.f );
	};

	extern cfg_t cfg;
}