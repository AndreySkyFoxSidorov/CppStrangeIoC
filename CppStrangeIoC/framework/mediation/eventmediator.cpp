





#include "EventMediator.h"

using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{

IEventDispatcher* EventMediator::getdispatcher() const
{
	return privatedispatcher;
}

void EventMediator::setdispatcher(IEventDispatcher* value)
{
	privatedispatcher = value;
}
}
}
}
}
