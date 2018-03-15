#pragma once
#include "MediationEvent.h"
#include <type_traits>

// FixiME Forward class Errrors:
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
class IView;
}
}
}
}
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
class IMediationBinding;
}
}
}
}

using namespace strange::framework::api;


namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
class IMediationBinder : public IBinder
{
	/// An event that just happened, and the View it happened to.
	/// If the event was Awake, it will trigger creation of a mapped Mediator.
public:
	virtual void Trigger( MediationEvent evt, IView* view ) = 0;

	/// Porcelain for Bind<T> providing a little extra clarity and security.
	template<typename T>
	IMediationBinding* BindView() = 0;
	static_assert( std::is_base_of<MonoBehaviour, T>::value, L"T must inherit from MonoBehaviour" );
};
}
}
}
}

