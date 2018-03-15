





#include "MediationBinder.h"
#include "MediationBinding.h"
#include "MediationException.h"


using namespace strange::extensions::injector::api;
using namespace strange::extensions::mediation::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{

IInjectionBinder* MediationBinder::getinjectionBinder() const
{
	return privateinjectionBinder;
}

void MediationBinder::setinjectionBinder(IInjectionBinder* value)
{
	privateinjectionBinder = value;
}

MediationBinder::MediationBinder()
{
}

IBinding* MediationBinder::GetRawBinding()
{
	MediationBinding tempVar(resolver);
	return dynamic_cast<IBinding*>(&tempVar);
}

void MediationBinder::Trigger(MediationEvent evt, IView* view)
{
	std::type_info viewType = view->GetType();
	IMediationBinding* binding = dynamic_cast<IMediationBinding*>(GetBinding(viewType));
	if(binding != nullptr)
	{
		switch(evt)
		{
		case MediationEvent::AWAKE:
			injectViewAndChildren(view);
			mapView(view, binding);
			break;
		case MediationEvent::DESTROYED:
			unmapView(view, binding);
			break;
		default:
			break;
		}
	}
	else if(evt == MediationEvent::AWAKE)
	{
		//Even if not mapped, Views (and their children) have potential to be injected
		injectViewAndChildren(view);
	}
}

void MediationBinder::injectViewAndChildren(IView* view)
{
	MonoBehaviour* mono = dynamic_cast<MonoBehaviour*>(view);
	std::vector<Component*> views = dynamic_cast<std::vector<Component*>>(mono->GetComponentsInChildren(IView::typeid, true));
	int aa = views.size();
	for(int a = aa - 1; a > -1; a--)
	{
		IView* iView = dynamic_cast<IView*>(views[a]);
		if(iView != nullptr)
		{
			if(iView->getautoRegisterWithContext() && iView->getregisteredWithContext())
			{
				continue;
			}
			iView->setregisteredWithContext(true);
			if(iView->Equals(mono) == false)
			{
				Trigger(MediationEvent::AWAKE, iView);
			}
		}
	}
	getinjectionBinder()->injector.Inject(mono, false);
}

template<typename T>
IBinding* MediationBinder::Bind()
{
	return Binder::Bind<T> ();
}

template<typename T>
IMediationBinding* MediationBinder::BindView()
{
	static_assert(std::is_base_of<MonoBehaviour, T>::value, L"T must inherit from MonoBehaviour");
	return dynamic_cast<IMediationBinding*>(Binder::Bind<T>());
}

void MediationBinder::mapView(IView* view, IMediationBinding* binding)
{
	std::type_info viewType = view->GetType();
	if(bindings->ContainsKey(viewType))
	{
		std::vector<void*> values = dynamic_cast<std::vector<void*>>(binding->value);
		int aa = values.size();
		for(int a = 0; a < aa; a++)
		{
			MonoBehaviour* mono = dynamic_cast<MonoBehaviour*>(view);
			std::type_info mediatorType = dynamic_cast<std::type_info*>(values [a]);
			if(mediatorType == viewType)
			{
				throw MediationException(viewType + L"mapped to itself. The result would be a stack overflow.", MediationExceptionType::MEDIATOR_VIEW_STACK_OVERFLOW);
			}
			MonoBehaviour* mediator = dynamic_cast<MonoBehaviour*>(mono->gameObject.AddComponent(mediatorType));
			if(mediator == nullptr)
			{
				//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
				throw MediationException(L"The view: " + viewType.ToString() + L" is mapped to mediator: " + mediatorType.ToString() + L". AddComponent resulted in null, which probably means " + mediatorType.ToString()->substr(mediatorType.ToString()->rfind(L".") + 1) + L" is not a MonoBehaviour.", MediationExceptionType::NULL_MEDIATOR);
			}
			if(dynamic_cast<IMediator*>(mediator) != nullptr)
			{
				(static_cast<IMediator*>(mediator))->PreRegister();
			}
			getinjectionBinder()->Bind(viewType).ToValue(view).ToInject(false);
			getinjectionBinder()->injector.Inject(mediator);
			getinjectionBinder()->Unbind(viewType);
			if(dynamic_cast<IMediator*>(mediator) != nullptr)
			{
				(static_cast<IMediator*>(mediator))->OnRegister();
			}
		}
	}
}

void MediationBinder::unmapView(IView* view, IMediationBinding* binding)
{
	std::type_info viewType = view->GetType();
	if(bindings->ContainsKey(viewType))
	{
		std::vector<void*> values = dynamic_cast<std::vector<void*>>(binding->value);
		int aa = values.size();
		for(int a = 0; a < aa; a++)
		{
			std::type_info mediatorType = dynamic_cast<std::type_info*>(values[a]);
			MonoBehaviour* mono = dynamic_cast<MonoBehaviour*>(view);
			IMediator* mediator = dynamic_cast<IMediator*>(mono->GetComponent(mediatorType));
			if(mediator != nullptr)
			{
				mediator->OnRemove();
			}
		}
	}
}

void MediationBinder::enableView(IView* view)
{
}

void MediationBinder::disableView(IView* view)
{
}
}
}
}
}
