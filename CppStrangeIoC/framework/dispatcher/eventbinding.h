#pragma once







#include <unordered_map>

using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::impl;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace eventdispatcher
{
namespace impl
{
class EventBinding : public Binding, public IEventBinding
{
private:
	std::unordered_map<Delegate*, EventCallbackType> callbackTypes;

public:
	EventBinding();

	EventBinding( strange::framework::impl::Binder::BindingResolver* resolver );

	EventCallbackType TypeForCallback( EmptyCallback callback );

	EventCallbackType TypeForCallback( EventCallback callback );

	IEventBinding* Bind( void* key );

	IEventBinding* To( EventCallback value );

	IEventBinding* To( EmptyCallback value );

	IEventBinding* To( void* value );

	void RemoveValue( void* value ) override;

private:
	void storeMethodType( Delegate* value );
};
}
}
}
}
}

