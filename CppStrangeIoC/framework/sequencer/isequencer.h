#pragma once
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace api
{
class ISequenceCommand;
}
}
}
}
namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace api
{
class ISequenceBinding;
}
}
}
}


using namespace strange::extensions::command::api;

namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace api
{
class ISequencer : public ICommandBinder
{
public:
	virtual void ReleaseCommand( ISequenceCommand* command ) = 0;

	template<typename T>
	ISequenceBinding* Bind() = 0;

	virtual ISequenceBinding* Bind( void* value ) = 0;
};
}
}
}
}

