#pragma once
#include <typeinfo>



using namespace strange::extensions::command::impl;
using namespace strange::extensions::sequencer::api;
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
class SequenceBinding : public CommandBinding, public ISequenceBinding
{
private:
	bool privateisOneOff = false;

public:
	bool getisOneOff() const;
	void setisOneOff( const bool& value );

	SequenceBinding();

	SequenceBinding( Binder::BindingResolver* resolver );

	ISequenceBinding* Once();

	//Everything below this point is simply facade on Binding to ensure fluent interface
	template<typename T>
	ISequenceBinding* Bind();

	ISequenceBinding* Bind( void* key );

	template<typename T>
	ISequenceBinding* To();

	ISequenceBinding* To( void* o );

	template<typename T>
	ISequenceBinding* ToName();

	ISequenceBinding* ToName( void* o );

	template<typename T>
	ISequenceBinding* Named();

	ISequenceBinding* Named( void* o );
};
}
}
}
}

