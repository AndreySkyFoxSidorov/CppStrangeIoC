#pragma once





using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace api
{
class IInjectionBinding : public IBinding
{
	/// Map the Binding to a Singleton so that every `GetInstance()` on the Binder Key returns the same imstance.
public:
	virtual IInjectionBinding* ToSingleton() = 0;

	/// Map the Binding to a stated instance so that every `GetInstance()` on the Binder Key returns the provided imstance. Sets type to Value
	virtual IInjectionBinding* ToValue( void* o ) = 0;

	/// Map the Binding to a stated instance so that every `GetInstance()` on the Binder Key returns the provided imstance. Does not set type.
	virtual IInjectionBinding* SetValue( void* o ) = 0;

	/// Map the binding and give access to all contexts in hierarchy
	virtual IInjectionBinding* CrossContext() = 0;

	virtual bool getisCrossContext() const = 0;

	/// Boolean setter to optionally override injection. If false, the instance will not be injected after instantiation.
	virtual IInjectionBinding* ToInject( bool value ) = 0;

	/// Get the parameter that specifies whether this Binding allows an instance to be injected
	virtual bool gettoInject() const = 0;

	/// Get and set the InjectionBindingType
	/// @see InjectionBindingType
	virtual InjectionBindingType* gettype() const = 0;
	virtual void settype( InjectionBindingType* value ) = 0;

	/// Bind is the same as Key, but permits Binder syntax: `Bind<T>().Bind<T>()`
	template<typename T>
	IInjectionBinding* Bind() = 0;

	/// Bind is the same as Key, but permits Binder syntax: `Bind<T>().Bind<T>()`
	virtual IInjectionBinding* Bind( void* key ) = 0;

	template<typename T>
	IInjectionBinding* To() = 0;
	virtual IInjectionBinding* To( void* o ) = 0;
	template<typename T>
	IInjectionBinding* ToName() = 0;
	virtual IInjectionBinding* ToName( void* o ) = 0;
	template<typename T>
	IInjectionBinding* Named() = 0;
	virtual IInjectionBinding* Named( void* o ) = 0;


	virtual void* getkey() const = 0;
	virtual void* getname() const = 0;
	virtual void* getvalue() const = 0;
	virtual Enum* getkeyConstraint() const = 0;
	virtual void setkeyConstraint( Enum* value ) = 0;
	virtual Enum* getvalueConstraint() const = 0;
	virtual void setvalueConstraint( Enum* value ) = 0;

};
}
}
}
}

