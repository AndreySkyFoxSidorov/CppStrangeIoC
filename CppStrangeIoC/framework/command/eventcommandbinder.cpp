#include "EventCommandBinder.h"

using namespace strange::extensions::command::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::pool::api;
namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{

EventCommandBinder::EventCommandBinder()
{
}

ICommand* EventCommandBinder::createCommand(void* cmd, void* data)
{
	injectionBinder::Bind<ICommand*> ().To(cmd);
	if(dynamic_cast<IEvent*>(data) != nullptr)
	{
		injectionBinder::Bind<IEvent*>().ToValue(data).ToInject(false);
	}
	ICommand* command = dynamic_cast<ICommand*>(injectionBinder::GetInstance<ICommand*>());
	if(command == nullptr)
	{
		std::wstring msg = L"A Command ";
		if(dynamic_cast<IEvent*>(data) != nullptr)
		{
			IEvent* evt = static_cast<IEvent*>(data);
			msg += L"tied to event " + evt->type;
		}
		msg += L" could not be instantiated.\nThis might be caused by a null pointer during instantiation or failing to override Execute (generally you shouldn't have constructor code in Commands).";
		throw CommandException(msg, CommandExceptionType::BAD_CONSTRUCTOR);
	}
	command->setdata(data);
	if(dynamic_cast<IEvent*>(data) != nullptr)
	{
		injectionBinder::Unbind<IEvent*>();
	}
	injectionBinder::Unbind<ICommand*> ();
	return command;
}

void EventCommandBinder::disposeOfSequencedData(void* data)
{
	if(dynamic_cast<IPoolable*>(data) != nullptr)
	{
		(dynamic_cast<IPoolable*>(data))->Release();
	}
}
}
}
}
}
