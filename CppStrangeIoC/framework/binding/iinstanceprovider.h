#pragma once







#include <typeinfo>



namespace strange
{
namespace framework
{
namespace api
{
class IInstanceProvider
{
	/// Retrieve an Instance based on the key.
	/// ex. `injectionBinder.Get<cISomeInterface>();`
public:
	template<typename T>
	T GetInstance() = 0;

	/// Retrieve an Instance based on the key.
	/// ex. `injectionBinder.Get(typeof(ISomeInterface));`
	virtual void* GetInstance( std::type_info key ) = 0;
};
}
}
}

