#pragma once





using namespace strange::extensions::injector::impl;
using namespace strange::extensions::injector::api;
using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace impl
{
class CrossContextInjectionBinder : public InjectionBinder, public ICrossContextInjectionBinder
{
private:
	IInjectionBinder* privateCrossContextBinder;

public:
	IInjectionBinder* getCrossContextBinder() const;
	void setCrossContextBinder( IInjectionBinder* value );

	CrossContextInjectionBinder();

	//SDM2014-0120: this function was already here, but the 2 overloads below were added as part of the cross-context implicit binding fix (thus this function was the clue to what
	template<typename T>
	IInjectionBinding* GetBinding() override;


	//SDM2014-0120: added as part of cross-Context implicit binding fix
	template<typename T>
	IInjectionBinding* GetBinding( void* name ) override; //without this override Binder.GetBinding(object,object) gets called instead of CrossContextInjectionBinder.GetBind

	//SDM2014-0120: added as part of cross-Context implicit binding fix
	IInjectionBinding* GetBinding( void* key ) override; //without this override Binder.GetBinding(object,object) gets called instead of CrossContextInjectionBinder.GetBinding(


	IInjectionBinding* GetBinding( void* key, void* name ) override;

	void ResolveBinding( IBinding* binding, void* key ) override;

protected:
	IInjector* GetInjectorForBinding( IInjectionBinding* binding ) override;
};
}
}
}
}
