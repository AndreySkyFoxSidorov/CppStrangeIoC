#pragma once







#include "Mediator.h"


using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{
class EventMediator : public Mediator
{
private:
	IEventDispatcher* privatedispatcher;

public:
	IEventDispatcher* getdispatcher() const;
	void setdispatcher( IEventDispatcher* value );

};
}
}
}
}

