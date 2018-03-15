#pragma once







#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include "exceptionhelper.h"

// FixiME Forward class Errrors:
namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace impl
{
class TmEvent;
}
}
}
}
}


using namespace strange::framework::api;
using namespace strange::framework::impl;
using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::pool::api;
using namespace strange::extensions::pool::impl;

namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace impl
{
class EventDispatcher : public Binder, public IEventDispatcher, public ITriggerProvider, public ITriggerable
{
	/// The list of clients that will be triggered as a consequence of an Event firing.
protected:
	std::unordered_set<ITriggerable*> triggerClients;
	std::unordered_set<ITriggerable*> triggerClientRemovals;
	bool isTriggeringClients = false;

	/// The eventPool is shared across all EventDispatchers for efficiency
public:
	static IPool<TmEvent*>* eventPool;

	EventDispatcher();

	IBinding* GetRawBinding() override;

	IEventBinding* Bind( void* key );

	void Dispatch( void* eventType );

#if defined(UNITY_EDITOR)
private:
	std::wstring eventTypeOld = L"";
#endif

public:
	void Dispatch( void* eventType, void* data );

protected:
	virtual IEvent* conformDataToEvent( void* eventType, void* data );

	virtual IEvent* createEvent( void* eventType, void* data );

	virtual void invokeEventCallback( void* data, EventCallback callback );

public:
	void AddListener( void* evt, EventCallback callback );

	void AddListener( void* evt, EmptyCallback callback );

	void RemoveListener( void* evt, EventCallback callback );

	void RemoveListener( void* evt, EmptyCallback callback );

	bool HasListener( void* evt, EventCallback callback );

	bool HasListener( void* evt, EmptyCallback callback );

	void UpdateListener( bool toAdd, void* evt, EventCallback callback );

	void UpdateListener( bool toAdd, void* evt, EmptyCallback callback );

	void AddTriggerable( ITriggerable* target );

	void RemoveTriggerable( ITriggerable* target );

	int getTriggerables() const;

protected:
	void flushRemovals();

public:
	template<typename T>
	bool Trigger( void* data );

	bool Trigger( void* key, void* data );

protected:
	void internalReleaseEvent( IEvent* evt );

public:
	void ReleaseEvent( IEvent* evt );

protected:
	void cleanEvent( IEvent* evt );
};

class EventInstanceProvider : public IInstanceProvider
{
public:
	template<typename T>
	T GetInstance();

	void* GetInstance( std::type_info key );
};
}
}
}
}
}
