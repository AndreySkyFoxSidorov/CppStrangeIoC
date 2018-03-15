#pragma once






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
class EventCommand : public Command
{
private:
	IEventDispatcher* privatedispatcher;
	IEvent* privateevt;

public:
	IEventDispatcher* getdispatcher() const;
	void setdispatcher( IEventDispatcher* value );

	IEvent* getevt() const;
	void setevt( IEvent* value );

	void Retain() override;

	void Release() override;
};
}
}
}
}

