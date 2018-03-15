#pragma once





namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace api
{
enum class EventCallbackType
{
	/// Indicates an EventCallback with no arguments
	NO_ARGUMENTS,
	/// Indicates an EventCallback with one argument
	ONE_ARGUMENT,
	/// Indicates no matching EventCallback could be found
	NOT_FOUND
};
}
}
}
}
}

