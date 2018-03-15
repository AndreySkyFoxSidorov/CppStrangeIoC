#pragma once







namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace api
{
enum class DispatcherExceptionType
{
	/// Injector Factory not found
	NULL_FACTORY,

	/// Callback must be a Delegate with zero or one argument
	ILLEGAL_CALLBACK_HANDLER
};
}
}
}
}

