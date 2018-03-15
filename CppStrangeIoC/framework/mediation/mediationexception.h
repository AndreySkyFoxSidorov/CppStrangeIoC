#pragma once







#include <string>
#include <stdexcept>


using namespace strange::extensions::mediation::api;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{
class MediationException : public std::exception
{
private:
	MediationExceptionType privatetype = static_cast<MediationExceptionType>( 0 );

public:
	MediationExceptionType gettype() const;
	void settype( const MediationExceptionType& value );

	MediationException();

	/// Constructs a MediationException with a message and MediationExceptionType
	MediationException( const std::wstring& message, MediationExceptionType exceptionType );
};
}
}
}
}

