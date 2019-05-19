#include "../csgo.hpp"

namespace hooks
{
	std::unordered_map<uint32_t, hook_t>& get_map()
	{
		static std::unordered_map<uint32_t, hook_t> map{};
		return map;
	}

	hook_handler_t& get()
	{
		static auto hook_handler = hook_handler_t();
		return hook_handler;
	}

	void init()
	{
		get();
	}

	void undo()
	{
		auto& map = get_map();

		for ( auto& map_entry : map )
		{
			map_entry.second.m_hook.unhook();
		}
	}
}
