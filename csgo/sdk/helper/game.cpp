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
}