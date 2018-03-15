#pragma once







#include <string>
#include <stdexcept>


using namespace strange::extensions::reflector::api;

namespace strange
{
namespace extensions
{
namespace reflector
{
namespace impl
{
class ReflectionException : public std::exception
{
private:
	ReflectionExceptionType privatetype = static_cast<ReflectionExceptionType>( 0 );

public:
	ReflectionExceptionType gettype() const;
	void settype( const ReflectionExceptionType& value );

	ReflectionException();

	/// Constructs a ReflectionException with a message and ReflectionExceptionType
	ReflectionException( const std::wstring& message, ReflectionExceptionType exceptionType );
};
}
}
}
}

