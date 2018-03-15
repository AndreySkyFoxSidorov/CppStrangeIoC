#pragma once







#include <vector>
#include <limits>
#include <typeinfo>

using namespace strange::extensions::reflector::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace reflector
{
namespace impl
{
class ReflectionBinder : public strange::framework::impl::Binder, public IReflectionBinder
{
public:
	ReflectionBinder();

	template<typename T>
	IReflectedClass* Get();

	IReflectedClass* Get( std::type_info type );

	IBinding* GetRawBinding() override;

private:
	void mapPreferredConstructor( IReflectedClass* reflected, IBinding* binding, std::type_info type );

	//Look for a constructor in the order:
	//1. Only one (just return it, since it's our only option)
	//2. Tagged with [Construct] tag
	//3. The constructor with the fewest parameters
	ConstructorInfo* findPreferredConstructor( std::type_info type );

	void mapPostConstructors( IReflectedClass* reflected, IBinding* binding, std::type_info type );

	void mapSetters( IReflectedClass* reflected, IBinding* binding, std::type_info type );

	/**
	 * Add an item to a list
	 */
	std::vector<void*> Add( void* value, std::vector<void*>& list );

	/**
	 * Add an item to a list
	 */
	std::vector<KeyValuePair<std::type_info, PropertyInfo*>> AddKV( KeyValuePair<std::type_info, PropertyInfo*>* value, std::vector<KeyValuePair<std::type_info, PropertyInfo*>>& list );
};

class PriorityComparer : public System::Collections::IComparer
{
public:
	int Compare( void* x, void* y );

private:
	int getPriority( MethodInfo* methodInfo );
};
}
}
}
}

