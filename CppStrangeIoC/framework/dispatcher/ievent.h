#pragma once







// FixiME Forward class Errrors:
namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace api
{
class IEventDispatcher;
}
}
}
}
}


namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace api
{
class IEvent
{
	/// The Event key
public:
	virtual void* gettype() const = 0;
	virtual void settype( void* value ) = 0;

	/// The IEventDispatcher that sent the event
	virtual IEventDispatcher* gettarget() const = 0;
	virtual void settarget( IEventDispatcher* value ) = 0;

	/// An arbitrary data payload
	virtual void* getdata() const = 0;
	virtual void setdata( void* value ) = 0;
};
}
}
}
}
}

