





#include "SignalException.h"

using namespace strange::extensions::signal::api;
namespace strange
{
namespace extensions
{
namespace signal
{
namespace impl
{

SignalExceptionType SignalException::gettype() const
{
	return privatetype;
}

void SignalException::settype(const SignalExceptionType& value)
{
	privatetype = value;
}

SignalException::SignalException() : Exception()
{
}

SignalException::SignalException(const std::wstring& message, SignalExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
