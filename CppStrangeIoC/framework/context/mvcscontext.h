#pragma once







#include <vector>
#include "exceptionhelper.h"

using namespace strange::extensions::implicitBind::api;
using namespace strange::extensions::implicitBind::impl;

using namespace strange::extensions::command::api;
using namespace strange::extensions::command::impl;
using namespace strange::extensions::context::api;
using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::api;
using namespace strange::extensions::dispatcher::eventdispatcher::impl;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::mediation::api;
using namespace strange::extensions::mediation::impl;
using namespace strange::extensions::sequencer::api;
using namespace strange::extensions::sequencer::impl;
using namespace strange::framework::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace context
{
namespace impl
{
class MVCSContext : public CrossContext
{
private:
	ICommandBinder* privatecommandBinder;
	IEventDispatcher* privatedispatcher;
	IMediationBinder* privatemediationBinder;
	IImplicitBinder* privateimplicitBinder;
	ISequencer* privatesequencer;

	/// A Binder that maps Events to Commands
public:
	ICommandBinder* getcommandBinder() const;
	void setcommandBinder( ICommandBinder* value );

	/// A Binder that serves as the Event bus for the Context
	IEventDispatcher* getdispatcher() const;
	void setdispatcher( IEventDispatcher* value );

	/// A Binder that maps Views to Mediators
	IMediationBinder* getmediationBinder() const;
	void setmediationBinder( IMediationBinder* value );

	//Interprets implicit bindings
	IImplicitBinder* getimplicitBinder() const;
	void setimplicitBinder( IImplicitBinder* value );

	/// A Binder that maps Events to Sequences
	ISequencer* getsequencer() const;
	void setsequencer( ISequencer* value );


	/// A list of Views Awake before the Context is fully set up.
protected:
	static ISemiBinding* viewCache;

public:
	MVCSContext();

	/// The recommended Constructor
	/// Just pass in the instance of your ContextView. Everything will begin automatically.
	/// Other constructors offer the option of interrupting startup at useful moments.
	MVCSContext( MonoBehaviour* view );

	MVCSContext( MonoBehaviour* view, ContextStartupFlags* flags );

	MVCSContext( MonoBehaviour* view, bool autoMapping );

	IContext* SetContextView( void* view ) override;

	/// Map the relationships between the Binders.
	/// Although you can override this method, it is recommended
	/// that you provide all your application bindings in `mapBindings()`.
protected:
	void addCoreComponents() override;

	void instantiateCoreComponents() override;

	void postBindings() override;

	/// Fires ContextEvent.START
	/// Whatever Command/Sequence you want to happen first should
	/// be mapped to this event.
public:
	void Launch() override;

	/// Gets an instance of the provided generic type.
	/// Always bear in mind that doing this risks adding
	/// dependencies that must be cleaned up when Contexts
	/// are removed.
	template<typename T>
	void* GetComponent() override;

	/// Gets an instance of the provided generic type and name from the InjectionBinder
	/// Always bear in mind that doing this risks adding
	/// dependencies that must be cleaned up when Contexts
	/// are removed.
	template<typename T>
	void* GetComponent( void* name ) override;

	void AddView( void* view ) override;

	void RemoveView( void* view ) override;

	/// Caches early-riser Views.
	///
	/// If a View is on stage at startup, it's possible for that
	/// View to be Awake before this Context has finished initing.
	/// `cacheView()` maintains a list of such 'early-risers'
	/// until the Context is ready to mediate them.
protected:
	virtual void cacheView( MonoBehaviour* view );

	/// Provide mediation for early-riser Views
	virtual void mediateViewCache();

	/// Clean up. Called by a ContextView in its OnDestroy method
public:
	void OnRemove() override;
};
}
}
}
}

