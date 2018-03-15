#pragma once







#include <string>
#include <stdexcept>



using namespace strange::extensions::pool::api;

namespace strange
{
namespace extensions
{
namespace pool
{
namespace impl
{
class PoolException : public std::exception
{
private:
	PoolExceptionType privatetype = static_cast<PoolExceptionType>( 0 );

public:
	PoolExceptionType gettype() const;
	void settype( const PoolExceptionType& value );

	PoolException();

	/// Constructs a PoolException with a message and PoolExceptionType
	PoolException( const std::wstring& message, PoolExceptionType exceptionType );
};
}
}
}
}

