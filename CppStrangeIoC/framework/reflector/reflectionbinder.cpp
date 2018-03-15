





#include "ReflectionBinder.h"
#include "ReflectedClass.h"
#include "ReflectionException.h"

using namespace strange::extensions::reflector::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace reflector
{
namespace impl
{

ReflectionBinder::ReflectionBinder()
{
}

template<typename T>
IReflectedClass* ReflectionBinder::Get()
{
	return Get(T::typeid);
}

IReflectedClass* ReflectionBinder::Get(std::type_info type)
{
	IBinding* binding = GetBinding(type);
	IReflectedClass* retv;
	if(binding == nullptr)
	{
		binding = GetRawBinding();
		IReflectedClass* reflected = new ReflectedClass();
		mapPreferredConstructor(reflected, binding, type);
		mapPostConstructors(reflected, binding, type);
		mapSetters(reflected, binding, type);
		binding->Bind(type).To(reflected);
		retv = dynamic_cast<IReflectedClass*>(binding->value);
		retv->setPreGenerated(false);
	}
	else
	{
		retv = dynamic_cast<IReflectedClass*>(binding->value);
		retv->setPreGenerated(true);
	}
	return retv;
}

IBinding* ReflectionBinder::GetRawBinding()
{
	IBinding* binding = strange::framework::impl::Binder::GetRawBinding();
	binding->valueConstraint = BindingConstraintType::ONE;
	return binding;
}

void ReflectionBinder::mapPreferredConstructor(IReflectedClass* reflected, IBinding* binding, std::type_info type)
{
	ConstructorInfo* constructor = findPreferredConstructor(type);
	if(constructor == nullptr)
	{
		throw ReflectionException(L"The reflector requires concrete classes.\nType " + type + L" has no constructor. Is it an interface?", ReflectionExceptionType::CANNOT_REFLECT_INTERFACE);
	}
	std::vector<ParameterInfo*> parameters = constructor->GetParameters();
	std::vector<std::type_info> paramList = std::vector<std::type_info*>(parameters.size());
	int i = 0;
	for(auto param : parameters)
	{
		std::type_info paramType = param->ParameterType;
		paramList [i] = paramType;
		i++;
	}
	reflected->setConstructor(constructor);
	reflected->setConstructorParameters(paramList);
}

ConstructorInfo* ReflectionBinder::findPreferredConstructor(std::type_info type)
{
	std::vector<ConstructorInfo*> constructors = type.GetConstructors(BindingFlags::FlattenHierarchy | BindingFlags::Public | BindingFlags::Instance | BindingFlags::InvokeMethod);
	if(constructors.size() == 1)
	{
		return constructors [0];
	}
	int len;
	int shortestLen = std::numeric_limits<int>::max();
	ConstructorInfo* shortestConstructor = nullptr;
	for(auto constructor : constructors)
	{
		std::vector<void*> taggedConstructors = constructor->GetCustomAttributes(Construct::typeid, true);
		if(taggedConstructors.size() > 0)
		{
			return constructor;
		}
		len = constructor->GetParameters().size();
		if(len < shortestLen)
		{
			shortestLen = len;
			shortestConstructor = constructor;
		}
	}
	return shortestConstructor;
}

void ReflectionBinder::mapPostConstructors(IReflectedClass* reflected, IBinding* binding, std::type_info type)
{
	std::vector<MethodInfo*> methods = type.GetMethods(BindingFlags::FlattenHierarchy | BindingFlags::Public | BindingFlags::Instance | BindingFlags::InvokeMethod);
	ArrayList* methodList = new ArrayList();
	for(auto method : methods)
	{
		std::vector<void*> tagged = method->GetCustomAttributes(PostConstruct::typeid, true);
		if(tagged.size() > 0)
		{
			methodList->Add(method);
		}
	}
	PriorityComparer tempVar();
	methodList->Sort(&tempVar);
	std::vector<MethodInfo*> postConstructors = static_cast<std::vector<MethodInfo*>>(methodList->ToArray(MethodInfo::typeid));
	reflected->setpostConstructors(postConstructors);
}

void ReflectionBinder::mapSetters(IReflectedClass* reflected, IBinding* binding, std::type_info type)
{
	std::vector<KeyValuePair<std::type_info, PropertyInfo*>> pairs(0);
	std::vector<void*> names(0);
	std::vector<MemberInfo*> privateMembers = type.FindMembers(MemberTypes::Property, BindingFlags::FlattenHierarchy | BindingFlags::SetProperty | BindingFlags::NonPublic | BindingFlags::Instance, nullptr, nullptr);
	for(auto member : privateMembers)
	{
		std::vector<void*> injections = member->GetCustomAttributes(Inject::typeid, true);
		if(injections.size() > 0)
		{
			throw ReflectionException(L"The class " + type.name() + L" has a non-public Injection setter " + member->Name + L". Make the setter public to allow injection.", ReflectionExceptionType::CANNOT_INJECT_INTO_NONPUBLIC_SETTER);
		}
	}
	std::vector<MemberInfo*> members = type.FindMembers(MemberTypes::Property, BindingFlags::FlattenHierarchy | BindingFlags::SetProperty | BindingFlags::Public | BindingFlags::Instance, nullptr, nullptr);
	for(auto member : members)
	{
		std::vector<void*> injections = member->GetCustomAttributes(Inject::typeid, true);
		if(injections.size() > 0)
		{
			Inject* attr = dynamic_cast<Inject*>(injections [0]);
			PropertyInfo* point = dynamic_cast<PropertyInfo*>(member);
			std::type_info pointType = point->PropertyType;
			KeyValuePair<std::type_info, PropertyInfo*>* pair = KeyValuePair<std::type_info, PropertyInfo*> (pointType, point);
			pairs = AddKV(*pair, pairs);
			auto bindingName = attr->name;
			names = Add(bindingName, names);
		}
	}
	reflected->setSetters(pairs);
	reflected->setSetterNames(names);
}

std::vector<void*> ReflectionBinder::Add(void* value, std::vector<void*>& list)
{
	std::vector<void*> tempList = list;
	int len = tempList.size();
	list = std::vector<void*>(len + 1);
	tempList.CopyTo(list, 0);
	list [len] = value;
	return list;
}

std::vector<KeyValuePair<std::type_info, PropertyInfo*>> ReflectionBinder::AddKV(KeyValuePair<std::type_info, PropertyInfo*>* value, std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& list)
{
	std::vector<KeyValuePair<std::type_info, PropertyInfo*>> tempList = list;
	int len = tempList.size();
	list = std::vector<KeyValuePair<std::type_info, PropertyInfo*>>(len + 1);
	tempList.CopyTo(list, 0);
	list [len] = *value;
	return list;
}

int PriorityComparer::Compare(void* x, void* y)
{
	int pX = getPriority(dynamic_cast<MethodInfo*>(x));
	int pY = getPriority(dynamic_cast<MethodInfo*>(y));
	return (pX < pY) ? -1 : 1;
}

int PriorityComparer::getPriority(MethodInfo* methodInfo)
{
	PostConstruct* attr = dynamic_cast<PostConstruct*>(methodInfo->GetCustomAttributes(true)[0]);
	int priority = attr->priority;
	return priority;
}
}
}
}
}
