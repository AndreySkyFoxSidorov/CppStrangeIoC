#pragma once







#include <string>
#include <stdexcept>


using namespace strange::extensions::injector::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{
class InjectionException : public std::exception
{
private:
	InjectionExceptionType privatetype = static_cast<InjectionExceptionType>( 0 );

public:
	InjectionExceptionType gettype() const;
	void settype( const InjectionExceptionType& value );

	InjectionException();

	/// Constructs an InjectionException with a message and InjectionExceptionType
	InjectionException( const std::wstring& message, InjectionExceptionType exceptionType );
};
}
}
}
}

