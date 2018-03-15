#pragma once





using namespace strange::extensions::reflector::api;
using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace api
{
class IInjector
{
	/// Request an instantiation based on the given binding.
	/// This request is made to the Injector, but it's really the InjectorFactory that does the instantiation.
public:
	virtual void* Instantiate( IInjectionBinding* binding ) = 0;

	/// Request that the provided target be injected.
	virtual void* Inject( void* target ) = 0;

	/// Request that the provided target be injected.
	virtual void* Inject( void* target, bool attemptConstructorInjection ) = 0;

	/// Clear the injections from the provided instance.
	/// Note that Uninject can only clean public properties...therefore only
	/// setters will be uninjected...not injections provided via constructor injection
	virtual void Uninject( void* target ) = 0;

	/// Get/set an InjectorFactory.
	virtual IInjectorFactory* getfactory() const = 0;
	virtual void setfactory( IInjectorFactory* value ) = 0;

	/// Get/set an InjectionBinder.
	virtual IInjectionBinder* getbinder() const = 0;
	virtual void setbinder( IInjectionBinder* value ) = 0;

	/// Get/set a ReflectionBinder.
	virtual IReflectionBinder* getreflector() const = 0;
	virtual void setreflector( IReflectionBinder* value ) = 0;
};
}
}
}
}

