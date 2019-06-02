#pragma once

namespace event_handler
{
	class listener : public IGameEventListener2
	{
	public:
		listener() = default;
		~listener() = default;

		void FireGameEvent( IGameEvent* p_event );
		int GetEventDebugID()
		{
			return 0x2A;
		};
	};

	void undo();

	void add( const std::string_view event_name, const std::function<void( IGameEvent* e )>& callback );
}