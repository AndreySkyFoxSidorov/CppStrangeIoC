





#include "Injector.h"

using namespace strange::extensions::injector::api;
using namespace strange::extensions::reflector::api;
namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{

Injector::Injector()
{
	InjectorFactory tempVar();
	setfactory(&tempVar);
}

IInjectorFactory* Injector::getfactory() const
{
	return privatefactory;
}

void Injector::setfactory(IInjectorFactory* value)
{
	privatefactory = value;
}

IInjectionBinder* Injector::getbinder() const
{
	return privatebinder;
}

void Injector::setbinder(IInjectionBinder* value)
{
	privatebinder = value;
}

IReflectionBinder* Injector::getreflector() const
{
	return privatereflector;
}

void Injector::setreflector(IReflectionBinder* value)
{
	privatereflector = value;
}

void* Injector::Instantiate(IInjectionBinding* binding)
{
	failIf(getbinder() == nullptr, L"Attempt to instantiate from Injector without a Binder", InjectionExceptionType::NO_BINDER);
	failIf(getfactory() == nullptr, L"Attempt to inject into Injector without a Factory", InjectionExceptionType::NO_FACTORY);
	armorAgainstInfiniteLoops(binding);
	auto retv = nullptr;
	std::type_info reflectionType = nullptr;
	if(dynamic_cast<std::type_info>(binding->value) != nullptr)
	{
		reflectionType = dynamic_cast<std::type_info*>(binding->value);
	}
	else if(binding->value == nullptr)
	{
		std::vector<void*> tl = dynamic_cast<std::vector<void*>>(binding->key);
		reflectionType = dynamic_cast<std::type_info*>(tl [0]);
		if(reflectionType.IsPrimitive || reflectionType == Decimal::typeid || reflectionType == std::wstring::typeid)
		{
			retv = binding->value;
		}
	}
	else
	{
		retv = binding->value;
	}
	if(retv == nullptr)  //If we don't have an existing value, go ahead and create one.
	{
		IReflectedClass* reflection = getreflector()->Get(reflectionType);
		std::vector<std::type_info> parameters = reflection->constructorParameters;
		int aa = parameters.size();
		std::vector<void*> args(aa);
		for(int a = 0; a < aa; a++)
		{
			args [a] = getValueInjection(dynamic_cast<std::type_info*>(parameters[a]), nullptr, nullptr);
		}
		retv = getfactory()->Get(binding, args);
		//If the InjectorFactory returns null, just return it. Otherwise inject the retv if it needs it
		//This could happen if Activator.CreateInstance returns null
		if(retv != nullptr)
		{
			if(binding->toInject)
			{
				retv = Inject(retv, false);
			}
			if(binding->type == InjectionBindingType::SINGLETON || binding->type == InjectionBindingType::VALUE)
			{
				//prevent double-injection
				binding->ToInject(false);
			}
		}
	}
	infinityLock.clear(); //Clear our infinity lock so the next time we instantiate we don't consider this a circular dependency
	return retv;
}

void* Injector::Inject(void* target)
{
	return Inject(target, true);
}

void* Injector::Inject(void* target, bool attemptConstructorInjection)
{
	failIf(getbinder() == nullptr, L"Attempt to inject into Injector without a Binder", InjectionExceptionType::NO_BINDER);
	failIf(getreflector() == nullptr, L"Attempt to inject without a reflector", InjectionExceptionType::NO_REFLECTOR);
	failIf(target == nullptr, L"Attempt to inject into null instance", InjectionExceptionType::NULL_TARGET);
	//Some things can't be injected into. Bail out.
	std::type_info t = target->GetType();
	if(t.IsPrimitive || t == Decimal::typeid || t == std::wstring::typeid)
	{
		return target;
	}
	IReflectedClass* reflection = getreflector()->Get(t);
	if(attemptConstructorInjection)
	{
		target = performConstructorInjection(target, reflection);
	}
	performSetterInjection(target, reflection);
	postInject(target, reflection);
	return target;
}

void Injector::Uninject(void* target)
{
	failIf(getbinder() == nullptr, L"Attempt to inject into Injector without a Binder", InjectionExceptionType::NO_BINDER);
	failIf(getreflector() == nullptr, L"Attempt to inject without a reflector", InjectionExceptionType::NO_REFLECTOR);
	failIf(target == nullptr, L"Attempt to inject into null instance", InjectionExceptionType::NULL_TARGET);
	std::type_info t = target->GetType();
	if(t.IsPrimitive || t == Decimal::typeid || t == std::wstring::typeid)
	{
		return;
	}
	IReflectedClass* reflection = getreflector()->Get(t);
	performUninjection(target, reflection);
}

void* Injector::performConstructorInjection(void* target, IReflectedClass* reflection)
{
	failIf(target == nullptr, L"Attempt to perform constructor injection into a null object", InjectionExceptionType::NULL_TARGET);
	failIf(reflection == nullptr, L"Attempt to perform constructor injection without a reflection", InjectionExceptionType::NULL_REFLECTION);
	ConstructorInfo* constructor = reflection->constructor;
	failIf(constructor == nullptr, L"Attempt to construction inject a null constructor", InjectionExceptionType::NULL_CONSTRUCTOR);
	std::vector<std::type_info> constructorParameters = reflection->constructorParameters;
	std::vector<void*> values(constructorParameters.size());
	int i = 0;
	for(auto type : constructorParameters)
	{
		values[i] = getValueInjection(type, nullptr, target);
		i++;
	}
	if(values.empty())
	{
		return target;
	}
	auto constructedObj = constructor->Invoke(values);
	return (constructedObj == nullptr) ? target : constructedObj;
}

void Injector::performSetterInjection(void* target, IReflectedClass* reflection)
{
	failIf(target == nullptr, L"Attempt to inject into a null object", InjectionExceptionType::NULL_TARGET);
	failIf(reflection == nullptr, L"Attempt to inject without a reflection", InjectionExceptionType::NULL_REFLECTION);
	failIf(reflection->setters->Length != reflection->setterNames->Length, L"Attempt to perform setter injection with mismatched names.\nThere must be exactly as many names as setters.", InjectionExceptionType::SETTER_NAME_MISMATCH);
	int aa = reflection->setters->Length;
	for(int a = 0; a < aa; a++)
	{
		KeyValuePair<std::type_info, PropertyInfo*>* pair = reflection->setters [a];
		auto value = getValueInjection(pair->first, reflection->setterNames[a], target);
		injectValueIntoPoint(value, target, pair->second);
	}
}

void* Injector::getValueInjection(std::type_info t, void* name, void* target)
{
	IInjectionBinding* binding = getbinder()->GetBinding(t, name);
	failIf(binding == nullptr, L"Attempt to Instantiate a null binding.", InjectionExceptionType::NULL_BINDING, t, name, target);
	if(binding->type == InjectionBindingType::VALUE)
	{
		if(!binding->toInject)
		{
			return binding->value;
		}
		else
		{
			auto retv = Inject(binding->value, false);
			binding->ToInject(false);
			return retv;
		}
	}
	else if(binding->type == InjectionBindingType::SINGLETON)
	{
		if(dynamic_cast<std::type_info>(binding->value) != nullptr || binding->value == nullptr)
		{
			Instantiate(binding);
		}
		return binding->value;
	}
	else
	{
		return Instantiate(binding);
	}
}

void Injector::injectValueIntoPoint(void* value, void* target, PropertyInfo* point)
{
	failIf(target == nullptr, L"Attempt to inject into a null target", InjectionExceptionType::NULL_TARGET);
	failIf(point == nullptr, L"Attempt to inject into a null point", InjectionExceptionType::NULL_INJECTION_POINT);
	failIf(value == nullptr, L"Attempt to inject null into a target object", InjectionExceptionType::NULL_VALUE_INJECTION);
	point->SetValue(target, value, nullptr);
}

void Injector::postInject(void* target, IReflectedClass* reflection)
{
	failIf(target == nullptr, L"Attempt to PostConstruct a null target", InjectionExceptionType::NULL_TARGET);
	failIf(reflection == nullptr, L"Attempt to PostConstruct without a reflection", InjectionExceptionType::NULL_REFLECTION);
	std::vector<MethodInfo*> postConstructors = reflection->postConstructors;
	if(postConstructors.size() > 0)
	{
		for(auto method : postConstructors)
		{
			method->Invoke(target, nullptr);
		}
	}
}

void Injector::performUninjection(void* target, IReflectedClass* reflection)
{
	int aa = reflection->setters->Length;
	for(int a = 0; a < aa; a++)
	{
		KeyValuePair<std::type_info, PropertyInfo*>* pair = reflection->setters [a];
		pair->second.SetValue(target, nullptr, nullptr);
	}
}

void Injector::failIf(bool condition, const std::wstring& message, InjectionExceptionType* type)
{
	failIf(condition, message, type, nullptr, nullptr, nullptr);
}

void Injector::failIf(bool condition, const std::wstring& message, InjectionExceptionType* type, std::type_info t, void* name)
{
	failIf(condition, message, type, t, name, nullptr);
}

void Injector::failIf(bool condition, const std::wstring& message, InjectionExceptionType* type, std::type_info t, void* name, void* target)
{
	if(condition)
	{
		message += L"\n\t\ttarget: " + target;
		message += L"\n\t\ttype: " + t;
		message += L"\n\t\tname: " + name;
		throw InjectionException(message, type);
	}
}

void Injector::armorAgainstInfiniteLoops(IInjectionBinding* binding)
{
	if(binding == nullptr)
	{
		return;
	}
	if(infinityLock.empty())
	{
		infinityLock = std::unordered_map<IInjectionBinding*, int> ();
	}
	if(infinityLock.find(binding) != infinityLock.end() == false)
	{
		infinityLock.emplace(binding, 0);
	}
	infinityLock [binding] = infinityLock [binding] + 1;
	if(infinityLock [binding] > INFINITY_LIMIT)
	{
		throw InjectionException("There appears to be a circular dependency. Terminating loop.", InjectionExceptionType::CIRCULAR_DEPENDENCY);
	}
}
}
}
}
}
