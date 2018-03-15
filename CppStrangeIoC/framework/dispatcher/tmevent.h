#pragma once






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
class TmEvent : public IEvent, public IPoolable
{
private:
	void* privatetype;
	IEventDispatcher* privatetarget;
	void* privatedata;

public:
	void* gettype() const;
	void settype( void* value );
	IEventDispatcher* gettarget() const;
	void settarget( IEventDispatcher* value );
	void* getdata() const;
	void setdata( void* value );

protected:
	int retainCount = 0;

public:
	TmEvent();

	/// Construct a TmEvent
	TmEvent( void* type, IEventDispatcher* target, void* data );

	//	#region IPoolable implementation

	void Restore();

	void Retain();

	void Release();

	bool getretain() const;

	//	#endregion
};
}
}
}
}
}
