





#include "InjectionBinder.h"

using namespace strange::framework::api;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::reflector::impl;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{

InjectionBinder::InjectionBinder()
{
	Injector tempVar();
	setinjector(&tempVar);
	getinjector()->binder = this;
	getinjector()->reflector = new ReflectionBinder();
}

void* InjectionBinder::GetInstance(std::type_info key)
{
	return GetInstance(key, nullptr);
}

void* InjectionBinder::GetInstance(std::type_info key, void* name)
{
	IInjectionBinding* binding = dynamic_cast<IInjectionBinding*>(GetBinding(key, name));
	if(binding == nullptr)
	{
		throw InjectionException("InjectionBinder has no binding for:\n\tkey: " + key + L"\nname: " + name, InjectionExceptionType::NULL_BINDING);
	}
	auto instance = GetInjectorForBinding(binding)->Instantiate(binding);
	return instance;
}

IInjector* InjectionBinder::GetInjectorForBinding(IInjectionBinding* binding)
{
	return getinjector();
}

template<typename T>
T InjectionBinder::GetInstance()
{
	auto instance = GetInstance(T::typeid);
	T retv = static_cast<T>(instance);
	return retv;
}

template<typename T>
T InjectionBinder::GetInstance(void* name)
{
	auto instance = GetInstance(T::typeid, name);
	T retv = static_cast<T>(instance);
	return retv;
}

IBinding* InjectionBinder::GetRawBinding()
{
	return new InjectionBinding(resolver);
}

IInjector* InjectionBinder::getinjector() const
{
	return _injector;
}

void InjectionBinder::setinjector(IInjector* value)
{
	if(_injector != nullptr)
	{
		_injector->binder = nullptr;
	}
	_injector = value;
	_injector->binder = this;
}

template<typename T>
IInjectionBinding* InjectionBinder::Bind()
{
	return dynamic_cast<IInjectionBinding*>(Binder::Bind<T>());
}

IInjectionBinding* InjectionBinder::Bind(std::type_info key)
{
	return dynamic_cast<IInjectionBinding*>(Binder::Bind(key));
}

template<typename T>
IInjectionBinding* InjectionBinder::GetBinding()
{
	return dynamic_cast<IInjectionBinding*>(Binder::GetBinding<T>());
}

template<typename T>
IInjectionBinding* InjectionBinder::GetBinding(void* name)
{
	return dynamic_cast<IInjectionBinding*>(Binder::GetBinding<T>(name));
}

IInjectionBinding* InjectionBinder::GetBinding(void* key)
{
	return dynamic_cast<IInjectionBinding*>(Binder::GetBinding(key));
}

IInjectionBinding* InjectionBinder::GetBinding(void* key, void* name)
{
	return dynamic_cast<IInjectionBinding*>(Binder::GetBinding(key, name));
}

int InjectionBinder::ReflectAll()
{
	std::vector<std::type_info> list;
	for(auto pair : bindings)
	{
		std::unordered_map<void*, IBinding*> dict = pair.second;
		for(auto bPair : dict)
		{
			IBinding* binding = dynamic_cast<IBinding*>(bPair.second);
			std::type_info t = (dynamic_cast<std::type_info>(binding->value) != nullptr) ? static_cast<std::type_info>(binding->value): binding->value->GetType();
			if(list.find(t) == -1)
			{
				list.push_back(t);
			}
		}
	}
	return Reflect(list);
}

int InjectionBinder::Reflect(std::vector<std::type_info>& list)
{
	int count = 0;
	for(auto t : list)
	{
		//Reflector won't permit primitive types, so screen them
		if(t.IsPrimitive || t == Decimal::typeid || t == std::wstring::typeid)
		{
			continue;
		}
		count++;
		getinjector()->reflector.Get(t);
	}
	return count;
}
}
}
}
}
