





#include "Sequencer.h"
#include "SequenceBinding.h"
#include "SequencerException.h"

using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::sequencer::api;
using namespace strange::extensions::command::api;
using namespace strange::extensions::command::impl;
using namespace strange::framework::api;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace impl
{

Sequencer::Sequencer()
{
}

IBinding* Sequencer::GetRawBinding()
{
	return new SequenceBinding(resolver);
}

void Sequencer::ReactTo(void* key, void* data)
{
	ISequenceBinding* binding = dynamic_cast<ISequenceBinding*>(GetBinding(key));
	if(binding != nullptr)
	{
		nextInSequence(binding, data, 0);
	}
}

void Sequencer::removeSequence(ISequenceCommand* command)
{
	if(activeSequences->ContainsKey(command))
	{
		command->Cancel();
		activeSequences->Remove(command);
	}
}

void Sequencer::invokeCommand(std::type_info cmd, ISequenceBinding* binding, void* data, int depth)
{
	ISequenceCommand* command = createCommand(cmd, data);
	command->sequenceId = depth;
	trackCommand(command, binding);
	executeCommand(command);
	ReleaseCommand(command);
}

ISequenceCommand* Sequencer::createCommand(void* cmd, void* data)
{
	injectionBinder::Bind<ISequenceCommand*> ().To(cmd);
	ISequenceCommand* command = dynamic_cast<ISequenceCommand*>(injectionBinder::GetInstance<ISequenceCommand*>());
	command->data = data;
	injectionBinder::Unbind<ISequenceCommand*> ();
	return command;
}

void Sequencer::trackCommand(ISequenceCommand* command, ISequenceBinding* binding)
{
	activeSequences [command] = binding;
}

void Sequencer::executeCommand(ISequenceCommand* command)
{
	if(command == nullptr)
	{
		return;
	}
	command->Execute();
}

void Sequencer::ReleaseCommand(ISequenceCommand* command)
{
	if(command->retain == false)
	{
		if(activeSequences->ContainsKey(command))
		{
			ISequenceBinding* binding = dynamic_cast<ISequenceBinding*>(activeSequences [command]);
			auto data = command->data;
			activeSequences->Remove(command);
			nextInSequence(binding, data, command->sequenceId + 1);
		}
	}
}

void Sequencer::nextInSequence(ISequenceBinding* binding, void* data, int depth)
{
	std::vector<void*> values = dynamic_cast<std::vector<void*>>(binding->value);
	if(depth < values.size())
	{
		std::type_info cmd = dynamic_cast<std::type_info>(values [depth]);
		invokeCommand(cmd, binding, data, depth);
	}
	else
	{
		if(binding->getisOneOff())
		{
			Unbind(binding);
		}
	}
}

void Sequencer::failIf(bool condition, const std::wstring& message, SequencerExceptionType type)
{
	if(condition)
	{
		throw SequencerException(message, type);
	}
}

template<typename T>
ISequenceBinding* Sequencer::Bind()
{
	return dynamic_cast<ISequenceBinding*>(CommandBinder::Bind<T>());
}

ISequenceBinding* Sequencer::Bind(void* value)
{
	return dynamic_cast<ISequenceBinding*>(CommandBinder::Bind(value));
}
}
}
}
}
