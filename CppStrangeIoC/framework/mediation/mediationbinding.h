#pragma once



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
class MediationBinding : public Binding, public IMediationBinding
{
public:
	MediationBinding( Binder::BindingResolver* resolver );

	template<typename T>
	IMediationBinding* ToMediator();
};
}
}
}
}

