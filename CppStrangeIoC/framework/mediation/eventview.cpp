





#include "EventView.h"

using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::context::api;
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{

IEventDispatcher* EventView::getdispatcher() const
{
	return privatedispatcher;
}

void EventView::setdispatcher(IEventDispatcher* value)
{
	privatedispatcher = value;
}
}
}
}
}
