#pragma once







#include "View.h"


using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::context::api;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{
class EventView : public View
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

