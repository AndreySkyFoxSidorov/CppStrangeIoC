#include "CommandBinding.h"

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

bool CommandBinding::getisOneOff() const
{
	return privateisOneOff;
}

void CommandBinding::setisOneOff(const bool& value)
{
	privateisOneOff = value;
}

bool CommandBinding::getisSequence() const
{
	return privateisSequence;
}

void CommandBinding::setisSequence(const bool& value)
{
	privateisSequence = value;
}

bool CommandBinding::getisPooled() const
{
	return privateisPooled;
}

void CommandBinding::setisPooled(const bool& value)
{
	privateisPooled = value;
}

CommandBinding::CommandBinding() : Binding()
{
}

CommandBinding::CommandBinding(Binder::BindingResolver* resolver) : Binding(resolver)
{
}

ICommandBinding* CommandBinding::Once()
{
	setisOneOff(true);
	return this;
}

ICommandBinding* CommandBinding::InParallel()
{
	setisSequence(false);
	return this;
}

ICommandBinding* CommandBinding::InSequence()
{
	setisSequence(true);
	return this;
}

ICommandBinding* CommandBinding::Pooled()
{
	setisPooled(true);
	resolver(this);
	return this;
}

template<typename T>
ICommandBinding* CommandBinding::Bind()
{
	return dynamic_cast<ICommandBinding*>(Binding::Bind<T>());
}

ICommandBinding* CommandBinding::Bind(void* key)
{
	return dynamic_cast<ICommandBinding*>(Binding::Bind(key));
}

template<typename T>
ICommandBinding* CommandBinding::To()
{
	return dynamic_cast<ICommandBinding*>(Binding::To<T>());
}

ICommandBinding* CommandBinding::To(void* o)
{
	return dynamic_cast<ICommandBinding*>(Binding::To(o));
}

template<typename T>
ICommandBinding* CommandBinding::ToName()
{
	return dynamic_cast<ICommandBinding*>(Binding::ToName<T>());
}

ICommandBinding* CommandBinding::ToName(void* o)
{
	return dynamic_cast<ICommandBinding*>(Binding::ToName(o));
}

template<typename T>
ICommandBinding* CommandBinding::Named()
{
	return dynamic_cast<ICommandBinding*>(Binding::Named<T>());
}

ICommandBinding* CommandBinding::Named(void* o)
{
	return dynamic_cast<ICommandBinding*>(Binding::Named(o));
}
}
}
}
}
