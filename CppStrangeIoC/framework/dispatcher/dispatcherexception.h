#pragma once







#include <string>
#include <stdexcept>


using namespace strange::extensions::dispatcher::api;

namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace impl
{
class DispatcherException : public std::exception
{
private:
	DispatcherExceptionType privatetype = static_cast<DispatcherExceptionType>( 0 );

public:
	DispatcherExceptionType gettype() const;
	void settype( const DispatcherExceptionType& value );

	DispatcherException();

	/// Constructs a DispatcherException with a message and DispatcherExceptionType
	DispatcherException( const std::wstring& message, DispatcherExceptionType exceptionType );
};
}
}
}
}

