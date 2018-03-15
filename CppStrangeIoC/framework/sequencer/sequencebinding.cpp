





#include "SequenceBinding.h"
#include "SequencerException.h"

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

bool SequenceBinding::getisOneOff() const
{
	return privateisOneOff;
}

void SequenceBinding::setisOneOff(const bool& value)
{
	privateisOneOff = value;
}

SequenceBinding::SequenceBinding() : CommandBinding()
{
}

SequenceBinding::SequenceBinding(Binder::BindingResolver* resolver) : CommandBinding(resolver)
{
}

ISequenceBinding* SequenceBinding::Once()
{
	setisOneOff(true);
	return this;
}

template<typename T>
ISequenceBinding* SequenceBinding::Bind()
{
	return Bind<T> ();
}

ISequenceBinding* SequenceBinding::Bind(void* key)
{
	return Bind(key);
}

template<typename T>
ISequenceBinding* SequenceBinding::To()
{
	return To(T::typeid);
}

ISequenceBinding* SequenceBinding::To(void* o)
{
	std::type_info oType = dynamic_cast<std::type_info>(o);
	std::type_info sType = ISequenceCommand::typeid;
	if(sType.IsAssignableFrom(oType) == false)
	{
		//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
		throw SequencerException(L"Attempt to bind a non SequenceCommand to a Sequence. Perhaps your command needs to extend SequenceCommand or implement ISequenCommand?\n\tType: " + oType.ToString(), SequencerExceptionType::COMMAND_USED_IN_SEQUENCE);
	}
	return dynamic_cast<ISequenceBinding*>(CommandBinding::To(o));
}

template<typename T>
ISequenceBinding* SequenceBinding::ToName()
{
	return dynamic_cast<ISequenceBinding*>(CommandBinding::ToName<T>());
}

ISequenceBinding* SequenceBinding::ToName(void* o)
{
	return dynamic_cast<ISequenceBinding*>(CommandBinding::ToName(o));
}

template<typename T>
ISequenceBinding* SequenceBinding::Named()
{
	return dynamic_cast<ISequenceBinding*>(CommandBinding::Named<T>());
}

ISequenceBinding* SequenceBinding::Named(void* o)
{
	return dynamic_cast<ISequenceBinding*>(CommandBinding::Named(o));
}
}
}
}
}
