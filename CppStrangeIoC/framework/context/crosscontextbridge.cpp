#include "CrossContextBridge.h"

using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::context::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{

IEventDispatcher* CrossContextBridge::getcrossContextDispatcher() const
{
	return privatecrossContextDispatcher;
}

void CrossContextBridge::setcrossContextDispatcher(IEventDispatcher* value)
{
	privatecrossContextDispatcher = value;
}

CrossContextBridge::CrossContextBridge()
{
}

IBinding* CrossContextBridge::Bind(void* key)
{
	IBinding* binding;
	binding = GetRawBinding();
	binding->Bind(key);
	resolver(binding);
	return binding;
}

template<typename T>
bool CrossContextBridge::Trigger(void* data)
{
	return Trigger(T::typeid, data);
}

bool CrossContextBridge::Trigger(void* key, void* data)
{
	IBinding* binding = GetBinding(key, nullptr);
	if(binding != nullptr && !std::find(eventsInProgress.begin(), eventsInProgress.end(), key) != eventsInProgress.end())
	{
		eventsInProgress.insert(key);
		getcrossContextDispatcher()->Dispatch(key, data);
		eventsInProgress.Remove(key);
	}
	return true;
}
}
}
}
}
