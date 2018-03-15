#pragma once




using namespace strange::extensions::command::api;
using namespace strange::extensions::sequencer::api;
using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace sequencer
{
namespace api
{
class ISequenceBinding : public ICommandBinding
{
	/// Declares that the Binding is a one-off. As soon as it's satisfied, it will be unmapped.
public:
	virtual ISequenceBinding* Once() = 0;

	/// Get/set the property set to `true` by `Once()`
	virtual bool getisOneOff() const = 0;
	virtual void setisOneOff( const bool& value ) = 0;

	template<typename T>
	ISequenceBinding* Bind() = 0;
	virtual ISequenceBinding* Bind( void* key ) = 0;
	template<typename T>
	ISequenceBinding* To() = 0;
	virtual ISequenceBinding* To( void* o ) = 0;
	template<typename T>
	ISequenceBinding* ToName() = 0;
	virtual ISequenceBinding* ToName( void* o ) = 0;
	template<typename T>
	ISequenceBinding* Named() = 0;
	virtual ISequenceBinding* Named( void* o ) = 0;
};
}
}
}
}

