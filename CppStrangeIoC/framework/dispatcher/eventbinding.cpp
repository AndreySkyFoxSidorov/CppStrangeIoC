#include "EventBinding.h"

using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;
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

EventBinding::EventBinding() : EventBinding(nullptr)
{
}

EventBinding::EventBinding(strange::framework::impl::Binder::BindingResolver* resolver) : Binding(resolver)
{
	keyConstraint = BindingConstraintType::ONE;
	valueConstraint = BindingConstraintType::MANY;
	callbackTypes = std::unordered_map<Delegate*, EventCallbackType> ();
}

EventCallbackType EventBinding::TypeForCallback(EmptyCallback callback)
{
	if(callbackTypes.find(callback) != callbackTypes.end())
	{
		return callbackTypes [callback];
	}
	return EventCallbackType::NOT_FOUND;
}

EventCallbackType EventBinding::TypeForCallback(EventCallback callback)
{
	if(callbackTypes.find(callback) != callbackTypes.end())
	{
		return callbackTypes [callback];
	}
	return EventCallbackType::NOT_FOUND;
}

IEventBinding* EventBinding::Bind(void* key)
{
	return dynamic_cast<IEventBinding*>(Binding::Bind(key));
}

IEventBinding* EventBinding::To(EventCallback value)
{
	Binding::To(value);
	storeMethodType(dynamic_cast<Delegate*>(value));
	return this;
}

IEventBinding* EventBinding::To(EmptyCallback value)
{
	Binding::To(value);
	storeMethodType(dynamic_cast<Delegate*>(value));
	return this;
}

IEventBinding* EventBinding::To(void* value)
{
	Binding::To(value);
	storeMethodType(dynamic_cast<Delegate*>(value));
	return this;
}

void EventBinding::RemoveValue(void* value)
{
	Binding::RemoveValue(value);
	callbackTypes.erase(dynamic_cast<Delegate*>(value));
}

void EventBinding::storeMethodType(Delegate* value)
{
	if(value == nullptr)
	{
		throw DispatcherException(L"EventDispatcher can't map something that isn't a delegate'", DispatcherExceptionType::ILLEGAL_CALLBACK_HANDLER);
	}
	MethodInfo* methodInfo = value->Method;
	int argsLen = methodInfo->GetParameters().size();
	switch(argsLen)
	{
	case 0:
		callbackTypes[value] = EventCallbackType::NO_ARGUMENTS;
		break;
	case 1:
		callbackTypes[value] = EventCallbackType::ONE_ARGUMENT;
		break;
	default:
		throw DispatcherException(L"Event callbacks must have either one or no arguments", DispatcherExceptionType::ILLEGAL_CALLBACK_HANDLER);
	}
}
}
}
}
}
}
