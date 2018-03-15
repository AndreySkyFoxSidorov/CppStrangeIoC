#pragma once





using namespace strange::extensions::context::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{
class Context : public Binder, public IContext
{
private:
	void* privatecontextView;

	/// The top of the View hierarchy.
	/// In MVCSContext, this is your top-level GameObject
public:
	void* getcontextView() const;
	void setcontextView( void* value );

	/// In a multi-Context app, this represents the first Context to instantiate.
	static IContext* firstContext;

	/// If false, the `Launch()` method won't fire.
	bool autoStartup = false;

	Context();

	Context( void* view, ContextStartupFlags flags );

	Context( void* view );

	Context( void* view, bool autoMapping );

	/// Override to add componentry. Or just extend MVCSContext.
protected:
	virtual void addCoreComponents();

	/// Override to instantiate componentry. Or just extend MVCSContext.
	virtual void instantiateCoreComponents();

	/// Set the object that represents the top of the Context hierarchy.
	/// In MVCSContext, this would be a GameObject.
public:
	virtual IContext* SetContextView( void* view );

	virtual void* GetContextView();

	/// Call this from your Root to set everything in action.
	virtual IContext* Start();

	/// The final method to fire after mappings.
	/// If autoStartup is false, you need to call this manually.
	virtual void Launch();

	/// Override to map project-specific bindings
protected:
	virtual void mapBindings();

	/// Override to do things after binding but before app launch
	virtual void postBindings();

	/// Add another Context to this one.
public:
	virtual IContext* AddContext( IContext* context );

	/// Remove a context from this one.
	virtual IContext* RemoveContext( IContext* context );

	/// Retrieve a component from this Context by generic type
	template<typename T>
	void* GetComponent();


	/// Retrieve a component from this Context by generic type and name
	template<typename T>
	void* GetComponent( void* name );

	/// Register a View with this Context
	virtual void AddView( void* view );

	/// Remove a View from this Context
	virtual void RemoveView( void* view );
};
}
}
}
}

