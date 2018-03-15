#include "DispatcherException.h"

using namespace strange::extensions::dispatcher::api;
namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace impl
{

DispatcherExceptionType DispatcherException::gettype() const
{
	return privatetype;
}

void DispatcherException::settype(const DispatcherExceptionType& value)
{
	privatetype = value;
}

DispatcherException::DispatcherException() : Exception()
{
}

DispatcherException::DispatcherException(const std::wstring& message, DispatcherExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
