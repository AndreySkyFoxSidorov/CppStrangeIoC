#pragma once







#include <vector>
#include <typeinfo>
#include "exceptionhelper.h"


using namespace strange::framework::api;
using namespace strange::framework::impl;
using namespace strange::extensions::injector::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{
class InjectionBinding : public Binding, public IInjectionBinding
{
private:
	InjectionBindingType* _type = InjectionBindingType::DEFAULT;
	bool _toInject = true;
	bool _isCrossContext = false;

public:
	virtual ~InjectionBinding()
	{
		delete _type;
	}

	InjectionBinding( Binder::BindingResolver* resolver );

	InjectionBindingType* gettype() const;
	void settype( InjectionBindingType* value );

	bool gettoInject() const;

	IInjectionBinding* ToInject( bool value );

	bool getisCrossContext() const;

	IInjectionBinding* ToSingleton();

	IInjectionBinding* ToValue( void* o );

	IInjectionBinding* SetValue( void* o );

protected:
	bool HasGenericAssignableFrom( std::type_info keyType, std::type_info objType );

	bool IsGenericTypeAssignable( std::type_info givenType, std::type_info genericType );

public:
	IInjectionBinding* CrossContext();

	template<typename T>
	IInjectionBinding* Bind();

	IInjectionBinding* Bind( void* key );

	template<typename T>
	IInjectionBinding* To();

	IInjectionBinding* To( void* o );

	template<typename T>
	IInjectionBinding* ToName();

	IInjectionBinding* ToName( void* o );

	template<typename T>
	IInjectionBinding* Named();

	IInjectionBinding* Named( void* o );
};
}
}
}
}
