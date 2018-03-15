#pragma once







#include <string>
#include <stdexcept>

using namespace strange::extensions::context::api;

namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{
class ContextException : public std::exception
{
private:
	ContextExceptionType privatetype = static_cast<ContextExceptionType>( 0 );

public:
	ContextExceptionType gettype() const;
	void settype( const ContextExceptionType& value );

	ContextException();

	/// Constructs a ContextException with a message and ContextExceptionType
	ContextException( const std::wstring& message, ContextExceptionType exceptionType );
};
}
}
}
}

