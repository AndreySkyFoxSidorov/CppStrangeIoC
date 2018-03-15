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
enum class EventDispatcherExceptionType
{
	/// Indicates that an event was fired with null as the key.
	EVENT_KEY_NULL,

	/// Indicates that the type of Event in the call and the type of Event in the payload don't match.
	EVENT_TYPE_MISMATCH,

	/// When attempting to fire a callback, the callback was discovered to be casting illegally.
	TARGET_INVOCATION
};
}
}
}
}
}

