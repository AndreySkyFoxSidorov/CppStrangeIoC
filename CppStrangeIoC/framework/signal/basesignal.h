#pragma once







#include <vector>
#include <typeinfo>
#include <functional>
#include "tangible_event.h"



using namespace strange::extensions::signal::api;

namespace strange
{
namespace extensions
{
namespace signal
{
namespace impl
{
class BaseSignal : public IBaseSignal
{
	/// The delegate for repeating listeners
public:
	TangibleEvent<System.Action<IBaseSignal, object[]>>* BaseListener = new TangibleEvent<System.Action<IBaseSignal, object[]>>();

	/// The delegate for one-off listeners
	TangibleEvent<System.Action<IBaseSignal, object[]>>* OnceBaseListener = new TangibleEvent<System.Action<IBaseSignal, object[]>>();

	void Dispatch( std::vector<void*>& args );

	virtual std::vector<std::type_info> GetTypes();

	void AddListener( std::function<void( IBaseSignal*, std::vector<void*> )> callback );

	void AddOnce( std::function<void( IBaseSignal*, std::vector<void*> )> callback );

	void RemoveListener( std::function<void( IBaseSignal*, std::vector<void*> )> callback );

};
}
}
}
}

