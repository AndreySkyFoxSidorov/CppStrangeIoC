#pragma once







#include <algorithm>

using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::context::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{
class CrossContextBridge : public Binder, public ITriggerable
{
private:
	IEventDispatcher* privatecrossContextDispatcher;

public:
	IEventDispatcher* getcrossContextDispatcher() const;
	void setcrossContextDispatcher( IEventDispatcher* value );

	/// Prevents the currently dispatching Event from cycling back on itself
protected:
	std::unordered_set<void*> eventsInProgress;

public:
	CrossContextBridge();

	IBinding* Bind( void* key ) override;

	//	#region ITriggerable implementation

	template<typename T>
	bool Trigger( void* data );

	bool Trigger( void* key, void* data );

	//	#endregion
};
}
}
}
}

