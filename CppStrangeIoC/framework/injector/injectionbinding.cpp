





#include "InjectionBinding.h"

using namespace strange::framework::api;
using namespace strange::framework::impl;
using namespace strange::extensions::injector::api;
namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{

InjectionBinding::InjectionBinding(Binder::BindingResolver* resolver)
{
	this->resolver = resolver;
	keyConstraint = BindingConstraintType::MANY;
	valueConstraint = BindingConstraintType::ONE;
}

InjectionBindingType* InjectionBinding::gettype() const
{
	return _type;
}

void InjectionBinding::settype(InjectionBindingType* value)
{
	_type = value;
}

bool InjectionBinding::gettoInject() const
{
	return _toInject;
}

IInjectionBinding* InjectionBinding::ToInject(bool value)
{
	_toInject = value;
	return this;
}

bool InjectionBinding::getisCrossContext() const
{
	return _isCrossContext;
}

IInjectionBinding* InjectionBinding::ToSingleton()
{
	//If already a value, this mapping is redundant
	if(gettype() == InjectionBindingType::VALUE)
	{
		return this;
	}
	settype(InjectionBindingType::SINGLETON);
	if(resolver != nullptr)
	{
		resolver(this);
	}
	return this;
}

IInjectionBinding* InjectionBinding::ToValue(void* o)
{
	settype(InjectionBindingType::VALUE);
	SetValue(o);
	return this;
}

IInjectionBinding* InjectionBinding::SetValue(void* o)
{
	if(o == nullptr)
	{
		UnityEngine::Debug::LogError(L"IInjectionBinding SetValue object == NULL");
		return nullptr;
	}
	std::type_info objType = o->GetType();
	std::vector<void*> keys = dynamic_cast<std::vector<void*>>(key);
	int aa = keys.size();
	//Check that value is legal for the provided keys
	for(int a = 0; a < aa; a++)
	{
		auto aKey = keys[a];
		std::type_info keyType = (dynamic_cast<std::type_info>(aKey) != nullptr) ? dynamic_cast<std::type_info>(aKey) : aKey->GetType();
		if(keyType.IsAssignableFrom(objType) == false && (HasGenericAssignableFrom(keyType, objType) == false))
		{
			throw InjectionException("Injection cannot bind a value that does not extend or implement the binding type.", InjectionExceptionType::ILLEGAL_BINDING_VALUE);
		}
	}
	To(o);
	return this;
}

bool InjectionBinding::HasGenericAssignableFrom(std::type_info keyType, std::type_info objType)
{
	//FIXME: We need to figure out how to determine generic assignability
	if(keyType.IsGenericType == false)
	{
		return false;
	}
	return true;
}

bool InjectionBinding::IsGenericTypeAssignable(std::type_info givenType, std::type_info genericType)
{
	auto interfaceTypes = givenType.GetInterfaces();
	for(auto it : interfaceTypes)
	{
		if(it.IsGenericType && it.GetGenericTypeDefinition() == genericType)
		{
			return true;
		}
	}
	if(givenType.IsGenericType && givenType.GetGenericTypeDefinition() == genericType)
	{
		return true;
	}
	std::type_info baseType = givenType.BaseType;
	if(baseType == nullptr)
	{
		return false;
	}
	return IsGenericTypeAssignable(baseType, genericType);
}

IInjectionBinding* InjectionBinding::CrossContext()
{
	_isCrossContext = true;
	if(resolver != nullptr)
	{
		resolver(this);
	}
	return this;
}

template<typename T>
IInjectionBinding* InjectionBinding::Bind()
{
	return dynamic_cast<IInjectionBinding*>(Binding::Bind<T>());
}

IInjectionBinding* InjectionBinding::Bind(void* key)
{
	return dynamic_cast<IInjectionBinding*>(Binding::Bind(key));
}

template<typename T>
IInjectionBinding* InjectionBinding::To()
{
	return dynamic_cast<IInjectionBinding*>(Binding::To<T>());
}

IInjectionBinding* InjectionBinding::To(void* o)
{
	return dynamic_cast<IInjectionBinding*>(Binding::To(o));
}

template<typename T>
IInjectionBinding* InjectionBinding::ToName()
{
	return dynamic_cast<IInjectionBinding*>(Binding::ToName<T>());
}

IInjectionBinding* InjectionBinding::ToName(void* o)
{
	return dynamic_cast<IInjectionBinding*>(Binding::ToName(o));
}

template<typename T>
IInjectionBinding* InjectionBinding::Named()
{
	return dynamic_cast<IInjectionBinding*>(Binding::Named<T>());
}

IInjectionBinding* InjectionBinding::Named(void* o)
{
	return dynamic_cast<IInjectionBinding*>(Binding::Named(o));
}
}
}
}
}
