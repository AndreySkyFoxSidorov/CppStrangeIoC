#pragma once







#include <string>
#include <stdexcept>


using namespace strange::framework::api;

namespace strange
{
namespace framework
{
namespace impl
{
class BinderException : public std::exception
{
private:
	BinderExceptionType privatetype = static_cast<BinderExceptionType>( 0 );

public:
	BinderExceptionType gettype() const;
	void settype( const BinderExceptionType& value );

	BinderException();

	/// Constructs a BinderException with a message and BinderExceptionType
	BinderException( const std::wstring& message, BinderExceptionType exceptionType );
};
}
}
}

