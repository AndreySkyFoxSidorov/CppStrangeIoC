#include "ContextException.h"

using namespace strange::extensions::context::api;
namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{

ContextExceptionType ContextException::gettype() const
{
	return privatetype;
}

void ContextException::settype(const ContextExceptionType& value)
{
	privatetype = value;
}

ContextException::ContextException() : Exception()
{
}

ContextException::ContextException(const std::wstring& message, ContextExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
