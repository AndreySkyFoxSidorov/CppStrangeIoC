#pragma once





using namespace strange::framework::api;
using namespace strange::extensions::dispatcher::api;

namespace strange
{
namespace extensions
{
namespace context
{
namespace api
{
class IContext : public IBinder
{
	/// Kicks off the internal Context binding/instantiation mechanisms
public:
	virtual IContext* Start() = 0;

	/// Fires ContextEvent.START (or the equivalent Signal) to launch the application
	virtual void Launch() = 0;

	/// Register a new context to this one
	virtual IContext* AddContext( IContext* context ) = 0;

	/// Remove a context from this one
	virtual IContext* RemoveContext( IContext* context ) = 0;

	/// Register a view with this context
	virtual void AddView( void* view ) = 0;

	/// Remove a view from this context
	virtual void RemoveView( void* view ) = 0;

	/// Get the ContextView
	virtual void* GetContextView() = 0;

};
}
}
}
}

