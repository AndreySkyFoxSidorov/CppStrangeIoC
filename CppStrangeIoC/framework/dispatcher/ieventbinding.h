#pragma once







#include "EventCallbackType.h"

// FixiME Forward class Errrors:
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
class IEvent;
}
}
}
}
}

using namespace strange::framework::api;

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
/// Delegate for adding a listener with a single argument
using EventCallback = std::function<void ( IEvent* payload )>;

/// Delegate for adding a listener with a no arguments
using EmptyCallback = std::function<void ()>;

class IEventBinding : public IBinding
{
	/// Retrieve the type of the provided callback
public:
	virtual EventCallbackType TypeForCallback( EventCallback callback ) = 0;

	/// Retrieve the type of the provided callback
	virtual EventCallbackType TypeForCallback( EmptyCallback callback ) = 0;

	virtual IEventBinding* Bind( void* key ) = 0;
	virtual IEventBinding* To( EventCallback callback ) = 0;
	virtual IEventBinding* To( EmptyCallback callback ) = 0;


};
}
}
}
}
}

