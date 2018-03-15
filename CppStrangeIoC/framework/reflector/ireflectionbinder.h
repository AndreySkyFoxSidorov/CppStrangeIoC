#pragma once







#include <typeinfo>

// FixiME Forward class Errrors:
namespace strange
{
namespace extensions
{
namespace reflector
{
namespace api
{
class IReflectedClass;
}
}
}
}

using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace reflector
{
namespace api
{
class IReflectionBinder
{
	/// Get a binding based on the provided Type
public:
	virtual IReflectedClass* Get( std::type_info type ) = 0;

	/// Get a binding based on the provided Type generic.
	template<typename T>
	IReflectedClass* Get() = 0;
};
}
}
}
}

