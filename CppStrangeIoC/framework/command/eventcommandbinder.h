#pragma once







#include <string>
#include "exceptionhelper.h"


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
class EventCommandBinder : public CommandBinder
{
public:
	EventCommandBinder();

	///
protected:
	ICommand* createCommand( void* cmd, void* data ) override;

	void disposeOfSequencedData( void* data ) override;
};
}
}
}
}

