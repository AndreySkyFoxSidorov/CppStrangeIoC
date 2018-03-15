#pragma once







#include "SequenceCommand.h"


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
class EventSequenceCommand : public SequenceCommand
{
private:
	IEventDispatcher* privatedispatcher;
	IEvent* privateevt;

	/// The context-wide Event bus
public:
	IEventDispatcher* getdispatcher() const;
	void setdispatcher( IEventDispatcher* value );

	/// The injected IEvent
	IEvent* getevt() const;
	void setevt( IEvent* value );
};
}
}
}
}

