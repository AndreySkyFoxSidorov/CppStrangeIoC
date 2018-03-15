





#include "InjectorFactory.h"

using namespace strange::extensions::injector::api;
namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{

InjectorFactory::InjectorFactory()
{
}

void* InjectorFactory::Get(IInjectionBinding* binding, std::vector<void*>& args)
{
	if(binding == nullptr)
	{
		throw InjectionException("InjectorFactory cannot act on null binding", InjectionExceptionType::NULL_BINDING);
	}
	InjectionBindingType* type = binding->type;
	switch(type)
	{
	case InjectionBindingType::SINGLETON:
		return singletonOf(binding, args);
	case InjectionBindingType::VALUE:
		return valueOf(binding);
	default:
		break;
	}
	return instanceOf(binding, args);
}

void* InjectorFactory::Get(IInjectionBinding* binding)
{
	return Get(binding, nullptr);
}

void* InjectorFactory::singletonOf(IInjectionBinding* binding, std::vector<void*>& args)
{
	if(binding->value != nullptr)
	{
		if(binding->value->GetType()->IsInstanceOfType(std::type_info::typeid))
		{
			auto o = createFromValue(binding->value, args);
			if(o == nullptr)
			{
				return nullptr;
			}
			binding->SetValue(o);
		}
		else
		{
			//no-op. We already have a binding value!
		}
	}
	else
	{
		auto generateImplicitValue = generateImplicit(static_cast < dynamic_cast<std::vector<void*>>(binding->key)*>([0]), args);
		if(generateImplicitValue != nullptr)
		{
			binding->SetValue(generateImplicitValue);
		}
		else
		{
			UnityEngine::Debug::LogError(L"IInjectionBinding generateImplicit object == NULL");
		}
	}
	return binding->value;
}

void* InjectorFactory::generateImplicit(void* key, std::vector<void*>& args)
{
	std::type_info type = dynamic_cast<std::type_info>(key);
	if(!type.IsInterface && !type.IsAbstract)
	{
		auto retValue = createFromValue(key, args);
		if(retValue != nullptr)
		{
			return retValue;
		}
		else
		{
			if(key != nullptr)
			{
				//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
				UnityEngine::Debug::LogError(L"generateImplicit object == NULL name:" + key->ToString());
			}
			if(args.size() > 0)
			{
				if(args.empty())
				{
					UnityEngine::Debug::LogError(L"generateImplicit object == NULL args.Length");
				}
			}
			else
			{
				UnityEngine::Debug::LogError(L"generateImplicit args == NULL");
			}
			throw InjectionException("InjectorFactory can't instantiate ERROR. Null Class", InjectionExceptionType::NOT_INSTANTIABLE);
		}
	}
	//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
	throw InjectionException("InjectorFactory can't instantiate an Interface or Abstract Class. Class: " + key->ToString(), InjectionExceptionType::NOT_INSTANTIABLE);
}

void* InjectorFactory::valueOf(IInjectionBinding* binding)
{
	return binding->value;
}

void* InjectorFactory::instanceOf(IInjectionBinding* binding, std::vector<void*>& args)
{
	if(binding->value != nullptr)
	{
		return createFromValue(binding->value, args);
	}
	auto value = generateImplicit(static_cast < dynamic_cast<std::vector<void*>>(binding->key)*>([0]), args);
	return createFromValue(value, args);
}

void* InjectorFactory::createFromValue(void* o, std::vector<void*>& args)
{
	std::type_info value = (dynamic_cast<std::type_info>(o) != nullptr) ? dynamic_cast<std::type_info>(o) : o->GetType();
	auto retv = nullptr;
	try
	{
		if(args.empty() || args.empty())
		{
			retv = Activator::CreateInstance(value);
		}
		else
		{
			retv = Activator::CreateInstance(value, args);
		}
	}
	catch(...)
	{
		//No-op
	}
	return retv;
}
}
}
}
}
