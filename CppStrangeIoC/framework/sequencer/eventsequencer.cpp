





#include "EventSequencer.h"

using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::sequencer::api;
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace impl
{

EventSequencer::EventSequencer()
{
}

ISequenceCommand* EventSequencer::createCommand(void* cmd, void* data)
{
	injectionBinder::Bind<ISequenceCommand*> ().To(cmd);
	if(dynamic_cast<IEvent*>(data) != nullptr)
	{
		injectionBinder::Bind<IEvent*> ().ToValue(data).ToInject(false);
	}
	ISequenceCommand* command = dynamic_cast<ISequenceCommand*>(injectionBinder::GetInstance<ISequenceCommand*>());
	command->data = data;
	if(dynamic_cast<IEvent*>(data) != nullptr)
	{
		injectionBinder::Unbind<IEvent*> ();
	}
	injectionBinder::Unbind<ISequenceCommand*> ();
	return command;
}
}
}
}
}
