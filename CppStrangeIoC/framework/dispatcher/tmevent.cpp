#include "TmEvent.h"

using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::pool::api;
namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace impl
{

void* TmEvent::gettype() const
{
	return privatetype;
}

void TmEvent::settype(void* value)
{
	privatetype = value;
}

IEventDispatcher* TmEvent::gettarget() const
{
	return privatetarget;
}

void TmEvent::settarget(IEventDispatcher* value)
{
	privatetarget = value;
}

void* TmEvent::getdata() const
{
	return privatedata;
}

void TmEvent::setdata(void* value)
{
	privatedata = value;
}

TmEvent::TmEvent()
{
}

TmEvent::TmEvent(void* type, IEventDispatcher* target, void* data)
{
	this->settype(type);
	this->settarget(target);
	this->setdata(data);
}

void TmEvent::Restore()
{
	this->settype(nullptr);
	this->settarget(nullptr);
	this->setdata(nullptr);
}

void TmEvent::Retain()
{
	retainCount++;
	//System.Console.WriteLine ("Retain: " + retainCount);
}

void TmEvent::Release()
{
	retainCount--;
	//System.Console.WriteLine ("Release: " + retainCount);
	if(retainCount == 0)
	{
		gettarget()->ReleaseEvent(this);
	}
}

bool TmEvent::getretain() const
{
	return retainCount > 0;
}
}
}
}
}
}
