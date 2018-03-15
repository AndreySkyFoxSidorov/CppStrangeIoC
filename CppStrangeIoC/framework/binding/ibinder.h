#pragma once







// FixiME Forward class Errrors:
namespace strange
{
namespace framework
{
namespace api
{
class IBinding;
}
}
}


namespace strange
{
namespace framework
{
namespace api
{
class IBinder
{
	/// Bind a Binding Key to a class or interface generic
public:
	template<typename T>
	IBinding* Bind() = 0;

	/// Bind a Binding Key to a value
	virtual IBinding* Bind( void* value ) = 0;

	/// Retrieve a binding based on the provided Type
	template<typename T>
	IBinding* GetBinding() = 0;

	/// Retrieve a binding based on the provided object
	virtual IBinding* GetBinding( void* key ) = 0;

	/// Retrieve a binding based on the provided Key (generic)/Name combo
	template<typename T>
	IBinding* GetBinding( void* name ) = 0;

	/// Retrieve a binding based on the provided Key/Name combo
	virtual IBinding* GetBinding( void* key, void* name ) = 0;

	/// Generate an unpopulated IBinding in whatever concrete form the Binder dictates
	virtual IBinding* GetRawBinding() = 0;

	/// Remove a binding based on the provided Key (generic)
	template<typename T>
	void Unbind() = 0;

	/// Remove a binding based on the provided Key (generic) / Name combo
	template<typename T>
	void Unbind( void* name ) = 0;

	/// Remove a binding based on the provided Key
	virtual void Unbind( void* key ) = 0;

	/// Remove a binding based on the provided Key / Name combo
	virtual void Unbind( void* key, void* name ) = 0;

	/// Remove the provided binding from the Binder
	virtual void Unbind( IBinding* binding ) = 0;

	/// Remove a select value from the given binding
	virtual void RemoveValue( IBinding* binding, void* value ) = 0;

	/// Remove a select key from the given binding
	virtual void RemoveKey( IBinding* binding, void* value ) = 0;

	/// Remove a select name from the given binding
	virtual void RemoveName( IBinding* binding, void* value ) = 0;

	/// The Binder is being removed
	/// Override this method to clean up remaining bindings
	virtual void OnRemove() = 0;

	/// <summary>
	/// Places individual Bindings into the bindings Dictionary as part of the resolving process
	/// </summary>
	/// Note that while some Bindings may store multiple keys, each key takes a unique position in the
	/// bindings Dictionary.
	///
	/// Conflicts in the course of fluent binding are expected, but GetBinding
	/// will throw an error if there are any unresolved conflicts.
	virtual void ResolveBinding( IBinding* binding, void* key ) = 0;
};
}
}
}

