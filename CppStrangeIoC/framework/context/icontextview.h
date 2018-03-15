#pragma once







// FixiME Forward class Errrors:
namespace strange
{
namespace extensions
{
namespace context
{
namespace api
{
class IContext;
}
}
}
}


using namespace strange::extensions::mediation::api;

namespace strange
{
namespace extensions
{
namespace context
{
namespace api
{
class IContextView : public IView
{
	/// Get and set the Context
public:
	virtual IContext* getcontext() const = 0;
	virtual void setcontext( IContext* value ) = 0;
};
}
}
}
}

