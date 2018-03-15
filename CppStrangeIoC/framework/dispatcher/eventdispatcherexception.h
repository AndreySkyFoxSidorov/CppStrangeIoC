#pragma once







#include <string>
#include <stdexcept>


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
class EventDispatcherException : public std::exception
{
private:
	EventDispatcherExceptionType privatetype = static_cast<EventDispatcherExceptionType>( 0 );

public:
	EventDispatcherExceptionType gettype() const;
	void settype( const EventDispatcherExceptionType& value );

	EventDispatcherException();

	/// Constructs an EventDispatcherException with a message and EventDispatcherExceptionType
	EventDispatcherException( const std::wstring& message, EventDispatcherExceptionType exceptionType );
};
}
}
}
}
}

