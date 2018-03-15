#include "Command.h"
#include "CommandException.h"

using namespace strange::extensions::command::api;
using namespace strange::extensions::injector::api;
using namespace strange::framework::api;
using namespace strange::extensions::pool::api;
namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{

ICommandBinder* Command::getcommandBinder() const
{
	return privatecommandBinder;
}

void Command::setcommandBinder(ICommandBinder* value)
{
	privatecommandBinder = value;
}

IInjectionBinder* Command::getinjectionBinder() const
{
	return privateinjectionBinder;
}

void Command::setinjectionBinder(IInjectionBinder* value)
{
	privateinjectionBinder = value;
}

void* Command::getdata() const
{
	return privatedata;
}

void Command::setdata(void* value)
{
	privatedata = value;
}

bool Command::getcancelled() const
{
	return privatecancelled;
}

void Command::setcancelled(const bool& value)
{
	privatecancelled = value;
}

bool Command::getIsClean() const
{
	return privateIsClean;
}

void Command::setIsClean(const bool& value)
{
	privateIsClean = value;
}

int Command::getsequenceId() const
{
	return privatesequenceId;
}

void Command::setsequenceId(const int& value)
{
	privatesequenceId = value;
}

Command::Command()
{
	//Set to false on construction to ensure that it's not double-injected on first use.
	//The pool will satisfy all injections on first use. The CommandBinder re-injects
	//every time the Command is recycled.
	setIsClean(false);
}

void Command::Execute()
{
	throw CommandException(L"You must override the Execute method in every Command", CommandExceptionType::EXECUTE_OVERRIDE);
}

void Command::Retain()
{
	setretain(true);
}

void Command::Release()
{
	setretain(false);
	if(getcommandBinder() != nullptr)
	{
		getcommandBinder()->ReleaseCommand(this);
	}
}

void Command::Restore()
{
	getinjectionBinder()->injector.Uninject(this);
	setIsClean(true);
}

void Command::Fail()
{
	if(getcommandBinder() != nullptr)
	{
		getcommandBinder()->Stop(this);
	}
}

void Command::Cancel()
{
	setcancelled(true);
}

bool Command::getretain() const
{
	return privateretain;
}

void Command::setretain(const bool& value)
{
	privateretain = value;
}
}
}
}
}
