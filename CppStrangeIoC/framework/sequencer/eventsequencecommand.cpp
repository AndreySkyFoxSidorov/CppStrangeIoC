





#include "EventSequenceCommand.h"

using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::sequencer::impl;
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace impl
{

IEventDispatcher* EventSequenceCommand::getdispatcher() const
{
	return privatedispatcher;
}

void EventSequenceCommand::setdispatcher(IEventDispatcher* value)
{
	privatedispatcher = value;
}

IEvent* EventSequenceCommand::getevt() const
{
	return privateevt;
}

void EventSequenceCommand::setevt(IEvent* value)
{
	privateevt = value;
}
}
}
}
}
