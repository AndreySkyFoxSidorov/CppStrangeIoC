#pragma once







#include <string>
#include <stdexcept>

using namespace strange::extensions::command::api;

namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{
class CommandException : public std::exception
{
private:
	CommandExceptionType privatetype = static_cast<CommandExceptionType>( 0 );

public:
	CommandExceptionType gettype() const;
	void settype( const CommandExceptionType& value );

	CommandException();

	/// Constructs a CommandException with a message and CommandExceptionType
	CommandException( const std::wstring& message, CommandExceptionType exceptionType );
};
}
}
}
}

