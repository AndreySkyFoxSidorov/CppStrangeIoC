





#include "MediationBinding.h"

using namespace strange::extensions::mediation::api;
using namespace strange::framework::impl;
namespace strange
{
namespace extensions
{
namespace mediation
{
namespace impl
{

MediationBinding::MediationBinding(Binder::BindingResolver* resolver) : Binding(resolver)
{
}

template<typename T>
IMediationBinding* MediationBinding::ToMediator()
{
	return dynamic_cast<IMediationBinding*>(Binding::To(T::typeid));
}
}
}
}
}
