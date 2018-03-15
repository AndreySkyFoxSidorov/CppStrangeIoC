#include "CrossContext.h"
#include "CrossContextBridge.h"

using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::injector::impl;
using namespace strange::framework::api;
namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{

ICrossContextInjectionBinder* CrossContext::getinjectionBinder() const
{
	CrossContextInjectionBinder tempVar();
	return (_injectionBinder != nullptr) ? _injectionBinder : (_injectionBinder = &tempVar);
}

void CrossContext::setinjectionBinder(ICrossContextInjectionBinder* value)
{
	_injectionBinder = value;
}

CrossContext::CrossContext() : Context()
{
}

CrossContext::CrossContext(void* view) : Context(view)
{
}

CrossContext::CrossContext(void* view, ContextStartupFlags flags) : Context(view, flags)
{
}

CrossContext::CrossContext(void* view, bool autoMapping) : Context(view, autoMapping)
{
}

void CrossContext::addCoreComponents()
{
	Context::addCoreComponents();
	if(getinjectionBinder()->CrossContextBinder == nullptr)  //Only null if it could not find a parent context / firstContext
	{
		getinjectionBinder()->CrossContextBinder = new CrossContextInjectionBinder();
	}
	if(firstContext == this)
	{
		getinjectionBinder()->Bind<IEventDispatcher*>().To<EventDispatcher*>().ToSingleton().ToName(ContextKeys::CROSS_CONTEXT_DISPATCHER).CrossContext();
		getinjectionBinder()->Bind<CrossContextBridge*> ().ToSingleton().CrossContext();
	}
}

void CrossContext::instantiateCoreComponents()
{
	Context::instantiateCoreComponents();
	IInjectionBinding* dispatcherBinding = getinjectionBinder()->GetBinding<IEventDispatcher*> (ContextKeys::CONTEXT_DISPATCHER);
	if(dispatcherBinding != nullptr)
	{
		IEventDispatcher* dispatcher = dynamic_cast<IEventDispatcher*>(getinjectionBinder()->GetInstance<IEventDispatcher*> (ContextKeys::CONTEXT_DISPATCHER));
		if(dispatcher != nullptr)
		{
			setcrossContextDispatcher(dynamic_cast<IEventDispatcher*>(getinjectionBinder()->GetInstance<IEventDispatcher*> (ContextKeys::CROSS_CONTEXT_DISPATCHER)));
			(dynamic_cast<ITriggerProvider*>(getcrossContextDispatcher()))->AddTriggerable(dynamic_cast<ITriggerable*>(dispatcher));
			(dynamic_cast<ITriggerProvider*>(dispatcher))->AddTriggerable(dynamic_cast<ITriggerable*>(getcrossContextBridge()));
		}
	}
}

IContext* CrossContext::AddContext(IContext* context)
{
	Context::AddContext(context);
	if(dynamic_cast<ICrossContextCapable*>(context) != nullptr)
	{
		AssignCrossContext(static_cast<ICrossContextCapable*>(context));
	}
	return this;
}

void CrossContext::AssignCrossContext(ICrossContextCapable* childContext)
{
	childContext->setcrossContextDispatcher(getcrossContextDispatcher());
	childContext->getinjectionBinder()->CrossContextBinder = getinjectionBinder()->CrossContextBinder;
}

void CrossContext::RemoveCrossContext(ICrossContextCapable* childContext)
{
	if(childContext->getcrossContextDispatcher() != nullptr)
	{
		(dynamic_cast<ITriggerProvider*>((childContext->getcrossContextDispatcher())))->RemoveTriggerable(dynamic_cast<ITriggerable*>(childContext->GetComponent<IEventDispatcher*>(ContextKeys::CONTEXT_DISPATCHER)));
		childContext->setcrossContextDispatcher(nullptr);
	}
}

IContext* CrossContext::RemoveContext(IContext* context)
{
	if(dynamic_cast<ICrossContextCapable*>(context) != nullptr)
	{
		RemoveCrossContext(static_cast<ICrossContextCapable*>(context));
	}
	return Context::RemoveContext(context);
}

IDispatcher* CrossContext::getcrossContextDispatcher() const
{
	return _crossContextDispatcher;
}

void CrossContext::setcrossContextDispatcher(IDispatcher* value)
{
	_crossContextDispatcher = dynamic_cast<IEventDispatcher*>(value);
}

IBinder* CrossContext::getcrossContextBridge() const
{
	if(_crossContextBridge == nullptr)
	{
		_crossContextBridge = dynamic_cast<IBinder*>(getinjectionBinder()->GetInstance<CrossContextBridge*> ());
	}
	return _crossContextBridge;
}

void CrossContext::setcrossContextBridge(IBinder* value)
{
	_crossContextDispatcher = dynamic_cast<IEventDispatcher*>(value);
}
}
}
}
}
