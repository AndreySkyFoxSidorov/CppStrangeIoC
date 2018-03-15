#pragma once







#include <vector>


namespace strange
{
namespace extensions
{
namespace injector
{
namespace api
{
class IInjectorFactory
{
	/// Request instantiation based on the provided binding
public:
	virtual void* Get( IInjectionBinding* binding ) = 0;

	/// Request instantiation based on the provided binding and an array of Constructor arguments
	virtual void* Get( IInjectionBinding* binding, std::vector<void*>& args ) = 0;
};
}
}
}
}

