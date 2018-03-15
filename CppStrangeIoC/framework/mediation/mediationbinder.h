#pragma once







#include <vector>
#include <typeinfo>
#include <type_traits>


using namespace strange::extensions::injector::api;
using namespace strange::extensions::mediation::api;
using namespace strange::framework::api;
using namespace strange::framework::impl;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{
class MediationBinder : public Binder, public IMediationBinder
{
private:
	IInjectionBinder* privateinjectionBinder;


public:
	IInjectionBinder* getinjectionBinder() const;
	void setinjectionBinder( IInjectionBinder* value );

	MediationBinder();


	IBinding* GetRawBinding() override;

	void Trigger( MediationEvent evt, IView* view );

	/// Initialize all IViews within this view
protected:
	virtual void injectViewAndChildren( IView* view );

public:
	template<typename T>
	IBinding* Bind() override;

	template<typename T>
	IMediationBinding* BindView();
	static_assert( std::is_base_of<MonoBehaviour, T>::value, L"T must inherit from MonoBehaviour" );

	/// Creates and registers one or more Mediators for a specific View instance.
	/// Takes a specific View instance and a binding and, if a binding is found for that type, creates and registers a Mediator.
protected:
	virtual void mapView( IView* view, IMediationBinding* binding );

	/// Removes a mediator when its view is destroyed
	virtual void unmapView( IView* view, IMediationBinding* binding );

private:
	void enableView( IView* view );

	void disableView( IView* view );
};
}
}
}
}

