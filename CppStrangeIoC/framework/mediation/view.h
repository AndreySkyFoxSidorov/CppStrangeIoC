#pragma once





using namespace strange::extensions::context::api;
using namespace strange::extensions::context::impl;
using namespace strange::extensions::mediation::api;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{
class View : public MonoBehaviour, public IView
{
private:
	bool privateregisteredWithContext = false;

	/// Leave this value true most of the time. If for some reason you want
	/// a view to exist outside a context you can set it to false. The only
	/// difference is whether an error gets generated.
	bool _requiresContext = true;
public:
	bool getrequiresContext() const;
	void setrequiresContext( const bool& value );

	/// A flag for allowing the View to register with the Context
	/// In general you can ignore this. But some developers have asked for a way of disabling
	///  View registration with a checkbox from Unity, so here it is.
	/// If you want to expose this capability either
	/// (1) uncomment the commented-out line immediately below, or
	/// (2) subclass View and override the autoRegisterWithContext method using your own custom (public) field.
	//[SerializeField]
protected:
	bool registerWithContext = true;
public:
	virtual bool getautoRegisterWithContext() const;
	virtual void setautoRegisterWithContext( const bool& value );

	bool getregisteredWithContext() const;
	void setregisteredWithContext( const bool& value );

	/// A MonoBehaviour Awake handler.
	/// The View will attempt to connect to the Context at this moment.
protected:
	virtual void Awake();

	/// A MonoBehaviour Start handler
	/// If the View is not yet registered with the Context, it will
	/// attempt to connect again at this moment.
	virtual void Start();

	/// A MonoBehaviour OnDestroy handler
	/// The View will inform the Context that it is about to be
	/// destroyed.
	virtual void OnDestroy();

	/// Recurses through Transform.parent to find the GameObject to which ContextView is attached
	/// Has a loop limit of 100 levels.
	/// By default, raises an Exception if no Context is found.
	virtual void bubbleToContext( MonoBehaviour* view, bool toAdd, bool finalTry );
};
}
}
}
}

