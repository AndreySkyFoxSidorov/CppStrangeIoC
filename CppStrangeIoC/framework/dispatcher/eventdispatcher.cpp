





#include "EventDispatcher.h"
#include "TmEvent.h"
#include "EventBinding.h"
#include "EventDispatcherException.h"

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

IPool<TmEvent*>* EventDispatcher::eventPool;

EventDispatcher::EventDispatcher()
{
	if(eventPool == nullptr)
	{
		eventPool = new Pool<TmEvent*> ();
		eventPool->instanceProvider = new EventInstanceProvider();
	}
}

IBinding* EventDispatcher::GetRawBinding()
{
	return new EventBinding(resolver);
}

IEventBinding* EventDispatcher::Bind(void* key)
{
	return dynamic_cast<IEventBinding*>(Binder::Bind(key));
}

void EventDispatcher::Dispatch(void* eventType)
{
	Dispatch(eventType, nullptr);
}

void EventDispatcher::Dispatch(void* eventType, void* data)
{
	//Scrub the data to make eventType and data conform if possible
	IEvent* evt = conformDataToEvent(eventType, data);
	if(dynamic_cast<IPoolable*>(evt) != nullptr)
	{
		(dynamic_cast<IPoolable*>(evt))->Retain();
	}
	bool continueDispatch = true;
	if(triggerClients != nullptr)
	{
		isTriggeringClients = true;
		for(auto trigger : triggerClients)
		{
			if(!trigger->Trigger(eventType, evt))
			{
				continueDispatch = false;
				break;
			}
		}
		if(triggerClientRemovals != nullptr)
		{
			flushRemovals();
		}
		isTriggeringClients = false;
	}
	if(!continueDispatch)
	{
		internalReleaseEvent(evt);
		return;
	}
	IEventBinding* binding = dynamic_cast<IEventBinding*>(GetBinding(eventType));
	if(binding == nullptr)
	{
		internalReleaseEvent(evt);
		return;
	}
	std::vector<void*> callbacks = dynamic_cast<std::vector<void*>>((dynamic_cast<std::vector<void*>>(binding->value))->Clone());
	if(callbacks.empty())
	{
		internalReleaseEvent(evt);
		return;
	}
	for(int a = 0; a < callbacks.size(); a++)
	{
		auto callback = callbacks[a];
		if(callback == nullptr)
		{
			continue;
		}
		callbacks[a] = nullptr;
		std::vector<void*> currentCallbacks = dynamic_cast<std::vector<void*>>(binding->value);
		if(Array::IndexOf(currentCallbacks, callback) == -1)
		{
			continue;
		}
		if(dynamic_cast<EventCallback>(callback) != nullptr)
		{
			invokeEventCallback(evt, dynamic_cast<EventCallback*>(callback));
		}
		else if(dynamic_cast<EmptyCallback>(callback) != nullptr)
		{
			static_cast<dynamic_cast<EmptyCallback*>(callback)*>();
		}
	}
	internalReleaseEvent(evt);
}

IEvent* EventDispatcher::conformDataToEvent(void* eventType, void* data)
{
	IEvent* retv = nullptr;
	if(eventType == nullptr)
	{
		throw EventDispatcherException(L"Attempt to Dispatch to null.\ndata: " + data, EventDispatcherExceptionType::EVENT_KEY_NULL);
	}
	else if(dynamic_cast<IEvent*>(eventType) != nullptr)
	{
		//Client provided a full-formed event
		retv = static_cast<IEvent*>(eventType);
	}
	else if(data == nullptr)
	{
		//Client provided just an event ID. Create an event for injection
		retv = createEvent(eventType, nullptr);
	}
	else if(dynamic_cast<IEvent*>(data) != nullptr)
	{
		//Client provided both an evertType and a full-formed IEvent
		retv = static_cast<IEvent*>(data);
	}
	else
	{
		//Client provided an eventType and some data which is not a IEvent.
		retv = createEvent(eventType, data);
	}
	return retv;
}

IEvent* EventDispatcher::createEvent(void* eventType, void* data)
{
	IEvent* retv = eventPool->GetInstance();
	retv->settype(eventType);
	retv->settarget(this);
	retv->setdata(data);
	return retv;
}

void EventDispatcher::invokeEventCallback(void* data, EventCallback callback)
{
	try
	{
		callback(dynamic_cast<IEvent*>(data));
	}
	catch(const InvalidCastException& e1)
	{
		auto tgt = callback->Target;
		std::wstring methodName = (dynamic_cast<Delegate*>(callback))->Method->Name;
		std::wstring message = L"An EventCallback is attempting an illegal cast. One possible reason is not typing the payload to IEvent in your callback. Another is illegal casting of the data.\nTarget class: " + tgt + L" method: " + methodName;
		throw EventDispatcherException(message, EventDispatcherExceptionType::TARGET_INVOCATION);
	}
}

void EventDispatcher::AddListener(void* evt, EventCallback callback)
{
	IBinding* binding = GetBinding(evt);
	if(binding == nullptr)
	{
		Bind(evt)->To(callback);
	}
	else
	{
		binding->To(callback);
	}
}

void EventDispatcher::AddListener(void* evt, EmptyCallback callback)
{
	IBinding* binding = GetBinding(evt);
	if(binding == nullptr)
	{
		Bind(evt)->To(callback);
	}
	else
	{
		binding->To(callback);
	}
}

void EventDispatcher::RemoveListener(void* evt, EventCallback callback)
{
	IBinding* binding = GetBinding(evt);
	RemoveValue(binding, callback);
}

void EventDispatcher::RemoveListener(void* evt, EmptyCallback callback)
{
	IBinding* binding = GetBinding(evt);
	RemoveValue(binding, callback);
}

bool EventDispatcher::HasListener(void* evt, EventCallback callback)
{
	IEventBinding* binding = dynamic_cast<IEventBinding*>(GetBinding(evt));
	if(binding == nullptr)
	{
		return false;
	}
	return binding->TypeForCallback(callback) != EventCallbackType::NOT_FOUND;
}

bool EventDispatcher::HasListener(void* evt, EmptyCallback callback)
{
	IEventBinding* binding = dynamic_cast<IEventBinding*>(GetBinding(evt));
	if(binding == nullptr)
	{
		return false;
	}
	return binding->TypeForCallback(callback) != EventCallbackType::NOT_FOUND;
}

void EventDispatcher::UpdateListener(bool toAdd, void* evt, EventCallback callback)
{
	if(toAdd)
	{
		AddListener(evt, callback);
	}
	else
	{
		RemoveListener(evt, callback);
	}
}

void EventDispatcher::UpdateListener(bool toAdd, void* evt, EmptyCallback callback)
{
	if(toAdd)
	{
		AddListener(evt, callback);
	}
	else
	{
		RemoveListener(evt, callback);
	}
}

void EventDispatcher::AddTriggerable(ITriggerable* target)
{
	if(triggerClients == nullptr)
	{
		triggerClients = std::unordered_set<ITriggerable*>();
	}
	triggerClients.insert(target);
}

void EventDispatcher::RemoveTriggerable(ITriggerable* target)
{
	if(std::find(triggerClients.begin(), triggerClients.end(), target) != triggerClients.end())
	{
		if(triggerClientRemovals == nullptr)
		{
			triggerClientRemovals = std::unordered_set<ITriggerable*>();
		}
		triggerClientRemovals.insert(target);
		if(!isTriggeringClients)
		{
			flushRemovals();
		}
	}
}

int EventDispatcher::getTriggerables() const
{
	if(triggerClients == nullptr)
	{
		return 0;
	}
	return triggerClients.size();
}

void EventDispatcher::flushRemovals()
{
	if(triggerClientRemovals == nullptr)
	{
		return;
	}
	for(auto target : triggerClientRemovals)
	{
		if(std::find(triggerClients.begin(), triggerClients.end(), target) != triggerClients.end())
		{
			triggerClients.Remove(target);
		}
	}
	triggerClientRemovals = nullptr;
}

template<typename T>
bool EventDispatcher::Trigger(void* data)
{
	return Trigger(T::typeid, data);
}

bool EventDispatcher::Trigger(void* key, void* data)
{
	bool allow = ((dynamic_cast<IEvent*>(data) != nullptr && System::Object::ReferenceEquals((dynamic_cast<IEvent*>(data))->gettarget(), this) == false) || (dynamic_cast<IEvent*>(key) != nullptr && System::Object::ReferenceEquals((dynamic_cast<IEvent*>(data))->gettarget(), this) == false));
	if(allow)
	{
		Dispatch(key, data);
	}
	return true;
}

void EventDispatcher::internalReleaseEvent(IEvent* evt)
{
	if(dynamic_cast<IPoolable*>(evt) != nullptr)
	{
		(dynamic_cast<IPoolable*>(evt))->Release();
	}
}

void EventDispatcher::ReleaseEvent(IEvent* evt)
{
	if((dynamic_cast<IPoolable*>(evt))->retain == false)
	{
		cleanEvent(evt);
		eventPool->ReturnInstance(evt);
	}
}

void EventDispatcher::cleanEvent(IEvent* evt)
{
	evt->settarget(nullptr);
	evt->setdata(nullptr);
	evt->settype(nullptr);
}

template<typename T>
T EventInstanceProvider::GetInstance()
{
	auto instance = new TmEvent();
	T retv = static_cast<T>(instance);
	return retv;
}

void* EventInstanceProvider::GetInstance(std::type_info key)
{
	return new TmEvent();
}
}
}
}
}
}
