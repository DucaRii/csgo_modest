#pragma once

class IGameEvent;
class IGameEventListener2;

class IGameEventManager2
{
public:
	virtual ~IGameEventManager2( void ) {};

	/// load game event descriptions from a file eg "resource\gameevents.res"
	virtual int LoadEventsFromFile( const char* filename ) = 0;

	/// removes all and anything
	virtual void Reset() = 0;

	/// adds a listener for a particular event
	virtual bool AddListener( IGameEventListener2* listener, const char* name, bool bServerSide ) = 0;

	/// returns true if this listener is listens to given event
	virtual bool FindListener( IGameEventListener2* listener, const char* name ) = 0;

	/// removes a listener 
	virtual void RemoveListener( IGameEventListener2* listener ) = 0;

	virtual void AddListenerGlobal( IGameEventListener2* listener, bool bIsServerSide ) = 0;

	/// create an event by name, but doesn't fire it. returns NULL is event is not
	/// known or no listener is registered for it. bForce forces the creation even if no listener is active
	virtual IGameEvent* CreateEvent( const char* name, bool bForce = false, int* pCookie = nullptr ) = 0;

	/// fires a server event created earlier, if bDontBroadcast is set, event is not send to clients
	virtual bool FireEvent( IGameEvent* event, bool bDontBroadcast = false ) = 0;

	/// fires an event for the local client only, should be used only by client code
	virtual bool FireEventClientSide( IGameEvent* event ) = 0;

	/// create a new copy of this event, must be free later
	virtual IGameEvent* DuplicateEvent( IGameEvent* event ) = 0;

	/// if an event was created but not fired for some reason, it has to bee freed, same UnserializeEvent
	virtual void FreeEvent( IGameEvent* event ) = 0;

	/// write/read event to/from bitbuffer
	virtual bool SerializeEvent( IGameEvent* event, int* buf ) = 0;
	virtual IGameEvent* UnserializeEvent( int* buf ) = 0;

	virtual void* GetEventDataTypes( IGameEvent* event ) = 0;
};

class IGameEventListener2
{
public:
	virtual    ~IGameEventListener2( void ) {};

	virtual void FireGameEvent( IGameEvent* event ) = 0;
	virtual int  GetEventDebugID( void ) = 0;
};