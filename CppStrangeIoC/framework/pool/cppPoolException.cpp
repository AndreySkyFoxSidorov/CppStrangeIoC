





#include "PoolException.h"

using namespace strange::extensions::pool::api;
namespace strange
{
namespace extensions
{
namespace pool
{
namespace impl
{

PoolExceptionType PoolException::gettype() const
{
	return privatetype;
}

void PoolException::settype(const PoolExceptionType& value)
{
	privatetype = value;
}

PoolException::PoolException() : Exception()
{
}

PoolException::PoolException(const std::wstring& message, PoolExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
