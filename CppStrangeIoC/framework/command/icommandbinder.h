#pragma once







// FixiME Forward class Errrors:
namespace strange
{
namespace extensions
{
namespace command
{
namespace api
{
class ICommand;
}
}
}
}
namespace strange
{
namespace extensions
{
namespace command
{
namespace api
{
class ICommandBinding;
}
}
}
}


using namespace strange::extensions::injector::api;
using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace command
{
namespace api
{
class ICommandBinder : public IBinder
{

	/// Trigger a key that unlocks one or more Commands
public:
	virtual void ReactTo( void* trigger ) = 0;

	/// Trigger a key that unlocks one or more Commands and provide a data injection to that Command
	virtual void ReactTo( void* trigger, void* data ) = 0;

	/// Release a previously retained Command.
	/// By default, a Command is garbage collected at the end of its `Execute()` method.
	/// But the Command can be retained for asynchronous calls.
	virtual void ReleaseCommand( ICommand* command ) = 0;

	/// Called to halt execution of a currently running command group
	virtual void Stop( void* key ) = 0;

	/// Bind a trigger Key by generic Type
	template<typename T>
	ICommandBinding* Bind() = 0;

	/// Bind a trigger Key by value
	virtual ICommandBinding* Bind( void* value ) = 0;

	template<typename T>
	ICommandBinding* GetBinding() = 0;
};
}
}
}
}

