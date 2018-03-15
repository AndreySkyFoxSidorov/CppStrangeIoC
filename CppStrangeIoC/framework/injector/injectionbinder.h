#pragma once







#include <string>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include "exceptionhelper.h"


using namespace strange::framework::api;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::reflector::impl;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{
class InjectionBinder : public Binder, public IInjectionBinder
{
private:
	IInjector* _injector;

public:
	virtual ~InjectionBinder()
	{
		delete _injector;
	}

	InjectionBinder();

	void* GetInstance( std::type_info key );

	virtual void* GetInstance( std::type_info key, void* name );

protected:
	virtual IInjector* GetInjectorForBinding( IInjectionBinding* binding );

public:
	template<typename T>
	T GetInstance();

	template<typename T>
	T GetInstance( void* name );

	IBinding* GetRawBinding() override;

	IInjector* getinjector() const;
	void setinjector( IInjector* value );

	template<typename T>
	IInjectionBinding* Bind();

	IInjectionBinding* Bind( std::type_info key );

	template<typename T>
	IInjectionBinding* GetBinding();

	//SDM2014-0120: "virtual" added as dictated by changes to CrossContextInjectionBinder in relation to the cross-context implicit binding fix
	template<typename T>
	IInjectionBinding* GetBinding( void* name );

	//SDM2014-0120: "virtual" added as dictated by changes to CrossContextInjectionBinder in relation to the cross-context implicit binding fix
	virtual IInjectionBinding* GetBinding( void* key );

	virtual IInjectionBinding* GetBinding( void* key, void* name );

	int ReflectAll();

	int Reflect( std::vector<std::type_info>& list );
};
}
}
}
}

