





#include "MediationException.h"

using namespace strange::extensions::mediation::api;
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{

MediationExceptionType MediationException::gettype() const
{
	return privatetype;
}

void MediationException::settype(const MediationExceptionType& value)
{
	privatetype = value;
}

MediationException::MediationException() : Exception()
{
}

MediationException::MediationException(const std::wstring& message, MediationExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
