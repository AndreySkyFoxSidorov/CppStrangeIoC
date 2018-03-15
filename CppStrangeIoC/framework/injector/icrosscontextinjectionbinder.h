#pragma once





using namespace strange::extensions::injector::api;
using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace injector
{
namespace api
{
class ICrossContextInjectionBinder : public IInjectionBinder
{
	//Cross-context Injection Binder is shared across all child contexts
public:
	virtual IInjectionBinder* getCrossContextBinder() const = 0;
	virtual void setCrossContextBinder( IInjectionBinder* value ) = 0;
};
}
}
}
}
