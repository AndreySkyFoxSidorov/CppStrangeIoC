#pragma once


using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
class IMediationBinding : public IBinding
{
	/// Porcelain for To<T> providing a little extra clarity and security.
public:
	template<typename T>
	IMediationBinding* ToMediator() = 0;
};
}
}
}
}

