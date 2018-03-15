#pragma once







#include "Context.h"


using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::injector::impl;
using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{
class CrossContext : public Context, public ICrossContextCapable
{
private:
	ICrossContextInjectionBinder* _injectionBinder;
	IBinder* _crossContextBridge;

	/// A Binder that handles dependency injection binding and instantiation
public:
	virtual ~CrossContext()
	{
		delete _injectionBinder;
		delete _crossContextBridge;
		delete _crossContextDispatcher;
	}

	ICrossContextInjectionBinder* getinjectionBinder() const;
	void setinjectionBinder( ICrossContextInjectionBinder* value );

	/// A specific instance of EventDispatcher that communicates
	/// across multiple contexts. An event sent across this
	/// dispatcher will be re-dispatched by the various context-wide
	/// dispatchers. So a dispatch to other contexts is simply
	///
	/// `crossContextDispatcher.Dispatch(MY_EVENT, payload)`;
	///
	/// Other contexts don't need to listen to the cross-context dispatcher
	/// as such, just map the necessary event to your local context
	/// dispatcher and you'll receive it.
protected:
	IEventDispatcher* _crossContextDispatcher;


public:
	CrossContext();

	CrossContext( void* view );

	CrossContext( void* view, ContextStartupFlags flags );

	CrossContext( void* view, bool autoMapping );

protected:
	void addCoreComponents() override;

	void instantiateCoreComponents() override;

public:
	IContext* AddContext( IContext* context ) override;

	virtual void AssignCrossContext( ICrossContextCapable* childContext );

	virtual void RemoveCrossContext( ICrossContextCapable* childContext );

	IContext* RemoveContext( IContext* context ) override;

	virtual IDispatcher* getcrossContextDispatcher() const;
	virtual void setcrossContextDispatcher( IDispatcher* value );

	virtual IBinder* getcrossContextBridge() const;
	virtual void setcrossContextBridge( IBinder* value );

};
}
}
}
}
