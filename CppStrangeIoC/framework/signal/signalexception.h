#pragma once







#include <string>
#include <stdexcept>


using namespace strange::extensions::signal::api;

namespace strange
{
namespace extensions
{
namespace signal
{
namespace impl
{
class SignalException : public std::exception
{
private:
	SignalExceptionType privatetype = static_cast<SignalExceptionType>( 0 );


public:
	SignalExceptionType gettype() const;
	void settype( const SignalExceptionType& value );
	SignalException();

	/// Constructs a SignalException with a message and SignalExceptionType
	SignalException( const std::wstring& message, SignalExceptionType exceptionType );

};
}
}
}
}

