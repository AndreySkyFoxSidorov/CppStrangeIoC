#include "CommandException.h"

using namespace strange::extensions::command::api;
namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{

CommandExceptionType CommandException::gettype() const
{
	return privatetype;
}

void CommandException::settype(const CommandExceptionType& value)
{
	privatetype = value;
}

CommandException::CommandException() : Exception()
{
}

CommandException::CommandException(const std::wstring& message, CommandExceptionType exceptionType) : Exception(message)
{
	settype(exceptionType);
}
}
}
}
}
