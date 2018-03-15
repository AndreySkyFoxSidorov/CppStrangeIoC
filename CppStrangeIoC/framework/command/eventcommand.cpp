#include "EventCommand.h"

using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::command::impl;
using namespace strange::extensions::pool::api;
namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{

IEventDispatcher* EventCommand::getdispatcher() const
{
	return privatedispatcher;
}

void EventCommand::setdispatcher(IEventDispatcher* value)
{
	privatedispatcher = value;
}

IEvent* EventCommand::getevt() const
{
	return privateevt;
}

void EventCommand::setevt(IEvent* value)
{
	privateevt = value;
}

void EventCommand::Retain()
{
	Command::Retain();
}

void EventCommand::Release()
{
	Command::Release();
}
}
}
}
}
