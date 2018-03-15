#pragma once







#include "Sequencer.h"


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
class EventSequencer : public Sequencer
{
public:
	EventSequencer();

	/// Instantiate and Inject the command, incling an IEvent to data.
protected:
	ISequenceCommand* createCommand( void* cmd, void* data ) override;
};
}
}
}
}

