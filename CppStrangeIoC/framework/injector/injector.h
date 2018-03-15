#pragma once







#include <string>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include "exceptionhelper.h"

using namespace strange::extensions::injector::api;
using namespace strange::extensions::reflector::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{
class Injector : public IInjector
{
private:
	IInjectorFactory* privatefactory;
	IInjectionBinder* privatebinder;
	IReflectionBinder* privatereflector;

	std::unordered_map<IInjectionBinding*, int> infinityLock;
	static constexpr int INFINITY_LIMIT = 10;

public:
	Injector();

	IInjectorFactory* getfactory() const;
	void setfactory( IInjectorFactory* value );
	IInjectionBinder* getbinder() const;
	void setbinder( IInjectionBinder* value );
	IReflectionBinder* getreflector() const;
	void setreflector( IReflectionBinder* value );

	void* Instantiate( IInjectionBinding* binding );

	void* Inject( void* target );

	void* Inject( void* target, bool attemptConstructorInjection );

	void Uninject( void* target );

private:
	void* performConstructorInjection( void* target, IReflectedClass* reflection );

	void performSetterInjection( void* target, IReflectedClass* reflection );

	void* getValueInjection( std::type_info t, void* name, void* target );

	//Inject the value into the target at the specified injection point
	void injectValueIntoPoint( void* value, void* target, PropertyInfo* point );

	//After injection, call any methods labelled with the [PostConstruct] tag
	void postInject( void* target, IReflectedClass* reflection );

	//Note that uninjection can only clean publicly settable points
	void performUninjection( void* target, IReflectedClass* reflection );

	void failIf( bool condition, const std::wstring& message, InjectionExceptionType* type );

	void failIf( bool condition, const std::wstring& message, InjectionExceptionType* type, std::type_info t, void* name );

	void failIf( bool condition, const std::wstring& message, InjectionExceptionType* type, std::type_info t, void* name, void* target );

	void armorAgainstInfiniteLoops( IInjectionBinding* binding );
};
}
}
}
}

