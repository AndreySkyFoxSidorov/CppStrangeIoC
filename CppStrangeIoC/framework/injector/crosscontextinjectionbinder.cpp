





#include "CrossContextInjectionBinder.h"

using namespace strange::extensions::injector::impl;
using namespace strange::extensions::injector::api;
using namespace strange::framework::api;
namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{

IInjectionBinder* CrossContextInjectionBinder::getCrossContextBinder() const
{
	return privateCrossContextBinder;
}

void CrossContextInjectionBinder::setCrossContextBinder(IInjectionBinder* value)
{
	privateCrossContextBinder = value;
}

CrossContextInjectionBinder::CrossContextInjectionBinder() : InjectionBinder()
{
}

template<typename T>
IInjectionBinding* CrossContextInjectionBinder::GetBinding()
{
	return GetBinding(T::typeid, nullptr);
}

template<typename T>
IInjectionBinding* CrossContextInjectionBinder::GetBinding(void* name)
{
	return GetBinding(T::typeid, name);
}

IInjectionBinding* CrossContextInjectionBinder::GetBinding(void* key)
{
	return GetBinding(key,nullptr);
}

IInjectionBinding* CrossContextInjectionBinder::GetBinding(void* key, void* name)
{
	IInjectionBinding* binding = dynamic_cast<IInjectionBinding*>(InjectionBinder::GetBinding(key, name));
	if(binding == nullptr)  //Attempt to get this from the cross context. Cross context is always SECOND PRIORITY. Local injections always override
	{
		if(getCrossContextBinder() != nullptr)
		{
			binding = dynamic_cast<IInjectionBinding*>(getCrossContextBinder()->GetBinding(key, name));
		}
	}
	return binding;
}

void CrossContextInjectionBinder::ResolveBinding(IBinding* binding, void* key)
{
	//Decide whether to resolve locally or not
	if(dynamic_cast<IInjectionBinding*>(binding) != nullptr)
	{
		InjectionBinding* injectionBinding = static_cast<InjectionBinding*>(binding);
		if(injectionBinding->isCrossContext)
		{
			if(getCrossContextBinder() == nullptr)  //We are a crosscontextbinder
			{
				InjectionBinder::ResolveBinding(binding, key);
			}
			else
			{
				Unbind(key, binding->name); //remove this cross context binding from the local binder
				getCrossContextBinder()->ResolveBinding(binding, key);
			}
		}
		else
		{
			InjectionBinder::ResolveBinding(binding, key);
		}
	}
}

IInjector* CrossContextInjectionBinder::GetInjectorForBinding(IInjectionBinding* binding)
{
	if(binding->isCrossContext && getCrossContextBinder() != nullptr)
	{
		return getCrossContextBinder()->injector;
	}
	else
	{
		return injector;
	}
}
}
}
}
}
