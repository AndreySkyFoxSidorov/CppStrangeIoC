





#include "SequenceCommand.h"
#include "SequencerException.h"

using namespace strange::extensions::command::impl;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::sequencer::api;
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace impl
{

ISequencer* SequenceCommand::getsequencer() const
{
	return privatesequencer;
}

void SequenceCommand::setsequencer(ISequencer* value)
{
	privatesequencer = value;
}

SequenceCommand::SequenceCommand()
{
}

void SequenceCommand::Fail()
{
	if(getsequencer() != nullptr)
	{
		getsequencer()->Stop(this);
	}
}

void SequenceCommand::Execute()
{
	throw SequencerException(L"You must override the Execute method in every SequenceCommand", SequencerExceptionType::EXECUTE_OVERRIDE);
}

void SequenceCommand::Release()
{
	retain = false;
	if(getsequencer() != nullptr)
	{
		getsequencer()->ReleaseCommand(this);
	}
}
}
}
}
}
