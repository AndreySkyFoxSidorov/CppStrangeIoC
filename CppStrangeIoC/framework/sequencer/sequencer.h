#pragma once







#include <string>
#include <vector>
#include <typeinfo>


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
class Sequencer : public CommandBinder, public ISequencer, public ITriggerable
{

public:
	Sequencer();

	IBinding* GetRawBinding() override;

	void ReactTo( void* key, void* data ) override;

private:
	void removeSequence( ISequenceCommand* command );

	void invokeCommand( std::type_info cmd, ISequenceBinding* binding, void* data, int depth );

	/// Instantiate and Inject the ISequenceCommand.
protected:
	virtual ISequenceCommand* createCommand( void* cmd, void* data );

private:
	void trackCommand( ISequenceCommand* command, ISequenceBinding* binding );

	void executeCommand( ISequenceCommand* command );

public:
	void ReleaseCommand( ISequenceCommand* command );

private:
	void nextInSequence( ISequenceBinding* binding, void* data, int depth );

	void failIf( bool condition, const std::wstring& message, SequencerExceptionType type );

public:
	template<typename T>
	ISequenceBinding* Bind();

	virtual ISequenceBinding* Bind( void* value );
};
}
}
}
}

