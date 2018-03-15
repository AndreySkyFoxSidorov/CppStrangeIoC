#pragma once






namespace strange
{
namespace extensions
{
namespace command
{
namespace api
{
enum class CommandExceptionType
{
	/// Commands must always override the Execute() method.
	EXECUTE_OVERRIDE,
	/// Binding wasn't found
	NULL_BINDING,
	/// Something went wrong during construction, so the Command resolved to null
	BAD_CONSTRUCTOR
};
}
}
}
}

