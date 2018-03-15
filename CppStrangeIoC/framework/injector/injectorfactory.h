#pragma once







#include <vector>
#include <typeinfo>
#include "exceptionhelper.h"


using namespace strange::extensions::injector::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{
class InjectorFactory : public IInjectorFactory
{

public:
	InjectorFactory();

	void* Get( IInjectionBinding* binding, std::vector<void*>& args );

	void* Get( IInjectionBinding* binding );

	/// Generate a Singleton instance
protected:
	void* singletonOf( IInjectionBinding* binding, std::vector<void*>& args );

	void* generateImplicit( void* key, std::vector<void*>& args );

	/// The binding already has a value. Simply return it.
	void* valueOf( IInjectionBinding* binding );

	/// Generate a new instance
	void* instanceOf( IInjectionBinding* binding, std::vector<void*>& args );

	/// Call the Activator to attempt instantiation the given object
	void* createFromValue( void* o, std::vector<void*>& args );
};
}
}
}
}

