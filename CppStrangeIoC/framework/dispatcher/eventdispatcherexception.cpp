#include "EventDispatcherException.h"

using namespace strange::extensions::dispatcher::eventdispatcher::api;
namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace impl
{

EventDispatcherExceptionType EventDispatcherException::gettype() const
{
	return privatetype;
}

void EventDispatcherException::settype(const EventDispatcherExceptionType& value)
{
	privatetype = value;
}

EventDispatcherException::EventDispatcherException() : Exception()
{
}

EventDispatcherException::EventDispatcherException(const std::wstring& message, EventDispatcherExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
}
