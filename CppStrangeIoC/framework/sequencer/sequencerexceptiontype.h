#pragma once



namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace api
{
enum class SequencerExceptionType
{
	/// SequenceCommands must always override the Execute() method.
	EXECUTE_OVERRIDE,

	/// This exception is raised if the mapped Command doesn't implement ISequenceCommand.
	COMMAND_USED_IN_SEQUENCE
};
}
}
}
}

