





#include "ReflectedClass.h"

using namespace strange::extensions::reflector::api;
namespace strange
{
namespace extensions
{
namespace reflector
{
namespace impl
{

ConstructorInfo* ReflectedClass::getConstructor() const
{
	return privateConstructor;
}

void ReflectedClass::setConstructor(ConstructorInfo* value)
{
	privateConstructor = value;
}

std::vector<std::type_info> ReflectedClass::getConstructorParameters() const
{
	return privateConstructorParameters;
}

void ReflectedClass::setConstructorParameters(const std::vector<std::type_info>& value)
{
	privateConstructorParameters = value;
}

std::vector<MethodInfo*> ReflectedClass::getPostConstructors() const
{
	return privatePostConstructors;
}

void ReflectedClass::setPostConstructors(std::vector<MethodInfo*>& value)
{
	privatePostConstructors = value;
}

std::vector<KeyValuePair<std::type_info, PropertyInfo*>> ReflectedClass::getSetters() const
{
	return privateSetters;
}

void ReflectedClass::setSetters(std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& value)
{
	privateSetters = value;
}

std::vector<void*> ReflectedClass::getSetterNames() const
{
	return privateSetterNames;
}

void ReflectedClass::setSetterNames(std::vector<void*>& value)
{
	privateSetterNames = value;
}

bool ReflectedClass::getPreGenerated() const
{
	return privatePreGenerated;
}

void ReflectedClass::setPreGenerated(const bool& value)
{
	privatePreGenerated = value;
}

ConstructorInfo* ReflectedClass::getconstructor() const
{
	return getConstructor();
}

void ReflectedClass::setconstructor(ConstructorInfo* value)
{
	setConstructor(value);
}

std::vector<std::type_info> ReflectedClass::getconstructorParameters() const
{
	return getConstructorParameters();
}

void ReflectedClass::setconstructorParameters(const std::vector<std::type_info>& value)
{
	setConstructorParameters(value);
}

std::vector<MethodInfo*> ReflectedClass::getpostConstructors() const
{
	return getPostConstructors();
}

void ReflectedClass::setpostConstructors(std::vector<MethodInfo*>& value)
{
	setPostConstructors(value);
}

std::vector<KeyValuePair<std::type_info, PropertyInfo*>> ReflectedClass::getsetters() const
{
	return getSetters();
}

void ReflectedClass::setsetters(std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& value)
{
	setSetters(value);
}

std::vector<void*> ReflectedClass::getsetterNames() const
{
	return getSetterNames();
}

void ReflectedClass::setsetterNames(std::vector<void*>& value)
{
	setSetterNames(value);
}

bool ReflectedClass::getpreGenerated() const
{
	return getPreGenerated();
}

void ReflectedClass::setpreGenerated(const bool& value)
{
	setPreGenerated(value);
}
}
}
}
}
