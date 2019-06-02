#include "../../csgo.hpp"

namespace event_handler
{
	listener m_listener;
	std::vector<std::pair<uint32_t, std::function<void( IGameEvent* )>>> m_callbacks = {};

	void listener::FireGameEvent( IGameEvent* e )
	{
		/// Go through all callbacks and check if the event matches
		for ( const auto& callback : m_callbacks )
		{
			/// If callback was found, call it!
			if ( HASH( e->GetName() ) == callback.first )
				callback.second( e );
		}
	}

	void undo()
	{
		ctx::csgo.events->RemoveListener( &m_listener );
	}

	void add( const std::string_view event_name, const std::function<void( IGameEvent * e )> & callback )
	{
		m_callbacks.push_back( std::make_pair( HASH( event_name.data() ), callback ) );

		ctx::csgo.events->AddListener( &m_listener, event_name.data(), false );
	}
}

