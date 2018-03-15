#pragma once






using namespace strange::extensions::command::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{
class CommandBinding : public Binding, public ICommandBinding
{
private:
	bool privateisOneOff = false;
	bool privateisSequence = false;
	bool privateisPooled = false;

public:
	bool getisOneOff() const;
	void setisOneOff( const bool& value );

	bool getisSequence() const;
	void setisSequence( const bool& value );

	bool getisPooled() const;
	void setisPooled( const bool& value );

	CommandBinding();

	CommandBinding( Binder::BindingResolver* resolver );

	ICommandBinding* Once();

	ICommandBinding* InParallel();

	ICommandBinding* InSequence();

	ICommandBinding* Pooled();

	//Everything below this point is simply facade on Binding to ensure fluent interface


	template<typename T>
	ICommandBinding* Bind();

	ICommandBinding* Bind( void* key );

	template<typename T>
	ICommandBinding* To();

	ICommandBinding* To( void* o );

	template<typename T>
	ICommandBinding* ToName();

	ICommandBinding* ToName( void* o );

	template<typename T>
	ICommandBinding* Named();

	ICommandBinding* Named( void* o );
};
}
}
}
}

