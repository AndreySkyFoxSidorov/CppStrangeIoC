





#include "ReflectionException.h"

using namespace strange::extensions::reflector::api;
namespace strange
{
namespace extensions
{
namespace reflector
{
namespace impl
{

ReflectionExceptionType ReflectionException::gettype() const
{
	return privatetype;
}

void ReflectionException::settype(const ReflectionExceptionType& value)
{
	privatetype = value;
}

ReflectionException::ReflectionException() : Exception()
{
}

ReflectionException::ReflectionException(const std::wstring& message, ReflectionExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
