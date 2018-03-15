





#include "InjectionException.h"

using namespace strange::extensions::injector::api;
namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{

InjectionExceptionType InjectionException::gettype() const
{
	return privatetype;
}

void InjectionException::settype(const InjectionExceptionType& value)
{
	privatetype = value;
}

InjectionException::InjectionException() : Exception()
{
}

InjectionException::InjectionException(const std::wstring& message, InjectionExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
