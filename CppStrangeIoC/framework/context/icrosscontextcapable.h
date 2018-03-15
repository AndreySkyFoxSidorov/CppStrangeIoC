#pragma once




using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::injector::api;

namespace strange
{
namespace extensions
{
namespace context
{
namespace api
{
class ICrossContextCapable
{
	/// Add cross-context functionality to a child context being added
public:
	virtual void AssignCrossContext( ICrossContextCapable* childContext ) = 0;

	/// Clean up cross-context functionality from a child context being removed
	virtual void RemoveCrossContext( ICrossContextCapable* childContext ) = 0;

	/// Request a component from the context (might be useful in certain cross-context situations)
	/// This is technically a deprecated methodology. Bind using CrossContext() instead.
	template<typename T>
	void* GetComponent() = 0;

	/// Request a component from the context (might be useful in certain cross-context situations)
	/// This is technically a deprecated methodology. Bind using CrossContext() instead.
	template<typename T>
	void* GetComponent( void* name ) = 0;

	/// All cross-context capable contexts must implement an injectionBinder
	virtual ICrossContextInjectionBinder* getinjectionBinder() const = 0;
	virtual void setinjectionBinder( ICrossContextInjectionBinder* value ) = 0;

	/// Set and get the shared system bus for communicating across contexts
	virtual IDispatcher* getcrossContextDispatcher() const = 0;
	virtual void setcrossContextDispatcher( IDispatcher* value ) = 0;

};
}
}
}
}
