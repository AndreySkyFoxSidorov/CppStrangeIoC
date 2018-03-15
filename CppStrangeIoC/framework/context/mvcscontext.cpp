#include "MVCSContext.h"

using namespace strange::extensions::implicitBind::api;
using namespace strange::extensions::implicitBind::impl;

using namespace strange::extensions::command::api;
using namespace strange::extensions::command::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::mediation::api;
using namespace strange::extensions::mediation::impl;
using namespace strange::extensions::sequencer::api;
using namespace strange::extensions::sequencer::impl;
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

ICommandBinder* MVCSContext::getcommandBinder() const
{
	return privatecommandBinder;
}

void MVCSContext::setcommandBinder(ICommandBinder* value)
{
	privatecommandBinder = value;
}

IEventDispatcher* MVCSContext::getdispatcher() const
{
	return privatedispatcher;
}

void MVCSContext::setdispatcher(IEventDispatcher* value)
{
	privatedispatcher = value;
}

IMediationBinder* MVCSContext::getmediationBinder() const
{
	return privatemediationBinder;
}

void MVCSContext::setmediationBinder(IMediationBinder* value)
{
	privatemediationBinder = value;
}

IImplicitBinder* MVCSContext::getimplicitBinder() const
{
	return privateimplicitBinder;
}

void MVCSContext::setimplicitBinder(IImplicitBinder* value)
{
	privateimplicitBinder = value;
}

ISequencer* MVCSContext::getsequencer() const
{
	return privatesequencer;
}

void MVCSContext::setsequencer(ISequencer* value)
{
	privatesequencer = value;
}

ISemiBinding* MVCSContext::viewCache = new SemiBinding();

MVCSContext::MVCSContext() : CrossContext()
{
}

MVCSContext::MVCSContext(MonoBehaviour* view) : CrossContext(view)
{
}

MVCSContext::MVCSContext(MonoBehaviour* view, ContextStartupFlags* flags) : CrossContext(view, flags)
{
}

MVCSContext::MVCSContext(MonoBehaviour* view, bool autoMapping) : CrossContext(view, autoMapping)
{
}

IContext* MVCSContext::SetContextView(void* view)
{
	contextView = (dynamic_cast<MonoBehaviour*>(view))->gameObject;
	if(contextView == nullptr)
	{
		throw ContextException("MVCSContext requires a ContextView of type MonoBehaviour", ContextExceptionType::NO_CONTEXT_VIEW);
	}
	return this;
}

void MVCSContext::addCoreComponents()
{
	CrossContext::addCoreComponents();
	injectionBinder::Bind<IInstanceProvider*>().Bind<IInjectionBinder*>().ToValue(injectionBinder);
	injectionBinder::Bind<IContext*>().ToValue(this).ToName(ContextKeys::CONTEXT);
	injectionBinder::Bind<ICommandBinder*>().To<EventCommandBinder*>().ToSingleton();
	//This binding is for local dispatchers
	injectionBinder::Bind<IEventDispatcher*>().To<EventDispatcher*>();
	//This binding is for the common system bus
	injectionBinder::Bind<IEventDispatcher*>().To<EventDispatcher*>().ToSingleton().ToName(ContextKeys::CONTEXT_DISPATCHER);
	injectionBinder::Bind<IMediationBinder*>().To<MediationBinder*>().ToSingleton();
	injectionBinder::Bind<ISequencer*>().To<EventSequencer*>().ToSingleton();
	injectionBinder::Bind<IImplicitBinder*>().To<ImplicitBinder*>().ToSingleton();
}

void MVCSContext::instantiateCoreComponents()
{
	CrossContext::instantiateCoreComponents();
	if(contextView == nullptr)
	{
		throw ContextException("MVCSContext requires a ContextView of type MonoBehaviour", ContextExceptionType::NO_CONTEXT_VIEW);
	}
	injectionBinder::Bind<GameObject*>().ToValue(contextView).ToName(ContextKeys::CONTEXT_VIEW);
	setcommandBinder(dynamic_cast<ICommandBinder*>(injectionBinder::GetInstance<ICommandBinder*>()));
	setdispatcher(dynamic_cast<IEventDispatcher*>(injectionBinder::GetInstance<IEventDispatcher*>(ContextKeys::CONTEXT_DISPATCHER)));
	setmediationBinder(dynamic_cast<IMediationBinder*>(injectionBinder::GetInstance<IMediationBinder*>()));
	setsequencer(dynamic_cast<ISequencer*>(injectionBinder::GetInstance<ISequencer*>()));
	setimplicitBinder(dynamic_cast<IImplicitBinder*>(injectionBinder::GetInstance<IImplicitBinder*>()));
	(dynamic_cast<ITriggerProvider*>(getdispatcher()))->AddTriggerable(dynamic_cast<ITriggerable*>(getcommandBinder()));
	(dynamic_cast<ITriggerProvider*>(getdispatcher()))->AddTriggerable(dynamic_cast<ITriggerable*>(getsequencer()));
}

void MVCSContext::postBindings()
{
	//It's possible for views to fire their Awake before bindings. This catches any early risers and attaches their Mediators.
	mediateViewCache();
	//Ensure that all Views underneath the ContextView are triggered
	getmediationBinder()->Trigger(MediationEvent::AWAKE, (dynamic_cast<GameObject*>(contextView))->GetComponent<ContextView*>());
}

void MVCSContext::Launch()
{
	getdispatcher()->Dispatch(ContextEvent::START);
}

template<typename T>
void* MVCSContext::GetComponent()
{
	return GetComponent<T>(nullptr);
}

template<typename T>
void* MVCSContext::GetComponent(void* name)
{
	IInjectionBinding* binding = injectionBinder::GetBinding<T>(name);
	if(binding != nullptr)
	{
		return injectionBinder::GetInstance<T>(name);
	}
	return nullptr;
}

void MVCSContext::AddView(void* view)
{
	if(getmediationBinder() != nullptr)
	{
		getmediationBinder()->Trigger(MediationEvent::AWAKE, dynamic_cast<IView*>(view));
	}
	else
	{
		cacheView(dynamic_cast<MonoBehaviour*>(view));
	}
}

void MVCSContext::RemoveView(void* view)
{
	getmediationBinder()->Trigger(MediationEvent::DESTROYED, dynamic_cast<IView*>(view));
}

void MVCSContext::cacheView(MonoBehaviour* view)
{
	if(viewCache->constraint->Equals(BindingConstraintType::ONE))
	{
		viewCache->constraint = BindingConstraintType::MANY;
	}
	viewCache->Add(view);
}

void MVCSContext::mediateViewCache()
{
	if(getmediationBinder() == nullptr)
	{
		throw ContextException("MVCSContext cannot mediate views without a mediationBinder", ContextExceptionType::NO_MEDIATION_BINDER);
	}
	std::vector<void*> values = dynamic_cast<std::vector<void*>>(viewCache->value);
	if(values.empty())
	{
		return;
	}
	int aa = values.size();
	for(int a = 0; a < aa; a++)
	{
		getmediationBinder()->Trigger(MediationEvent::AWAKE, dynamic_cast<IView*>(values[a]));
	}
	viewCache = new SemiBinding();
}

void MVCSContext::OnRemove()
{
	CrossContext::OnRemove();
	getcommandBinder()->OnRemove();
}
}
}
}
}
