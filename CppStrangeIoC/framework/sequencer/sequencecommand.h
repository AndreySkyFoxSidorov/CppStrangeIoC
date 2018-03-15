#pragma once

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
class SequenceCommand : public Command, public ISequenceCommand
{
private:
	ISequencer* privatesequencer;

public:
	ISequencer* getsequencer() const;
	void setsequencer( ISequencer* value );

	SequenceCommand();

	void Fail();

	virtual void Execute();

	void Release();
};
}
}
}
}

