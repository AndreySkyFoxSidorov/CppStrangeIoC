#pragma once







#include <vector>
#include <typeinfo>

using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace api
{
class IInjectionBinder : public IInstanceProvider
{
	/// Get or set an Injector to use. By default, Injector instantiates it's own, but that can be overridden.
public:
	virtual IInjector* getinjector() const = 0;
	virtual void setinjector( IInjector* value ) = 0;

	/// Retrieve an Instance based on a key/name combo.
	/// ex. `injectionBinder.Get(typeof(ISomeInterface), SomeEnum.MY_ENUM);`
	virtual void* GetInstance( std::type_info key, void* name ) = 0;

	/// Retrieve an Instance based on a key/name combo.
	/// ex. `injectionBinder.Get<cISomeInterface>(SomeEnum.MY_ENUM);`
	template<typename T>
	T GetInstance( void* name ) = 0;

	/// Reflect all the types in the list
	/// Return the number of types in the list, which should be equal to the list length
	virtual int Reflect( std::vector<std::type_info>& list ) = 0;

	/// Reflect all the types currently registered with InjectionBinder
	/// Return the number of types reflected, which should be equal to the number
	/// of concrete classes you've mapped.
	virtual int ReflectAll() = 0;

	/// <summary>
	/// Places individual Bindings into the bindings Dictionary as part of the resolving process
	/// </summary>
	/// Note that while some Bindings may store multiple keys, each key takes a unique position in the
	/// bindings Dictionary.
	///
	/// Conflicts in the course of fluent binding are expected, but GetBinding
	/// will throw an error if there are any unresolved conflicts.
	virtual void ResolveBinding( IBinding* binding, void* key ) = 0;

	template<typename T>
	IInjectionBinding* Bind() = 0;
	virtual IInjectionBinding* Bind( std::type_info key ) = 0;
	virtual IBinding* Bind( void* key ) = 0;
	template<typename T>
	IInjectionBinding* GetBinding() = 0;
	template<typename T>
	IInjectionBinding* GetBinding( void* name ) = 0;
	virtual IInjectionBinding* GetBinding( void* key ) = 0;
	virtual IInjectionBinding* GetBinding( void* key, void* name ) = 0;
	template<typename T>
	void Unbind() = 0;
	template<typename T>
	void Unbind( void* name ) = 0;
	virtual void Unbind( void* key ) = 0;
	virtual void Unbind( void* key, void* name ) = 0;
	virtual void Unbind( IBinding* binding ) = 0;
};
}
}
}
}

