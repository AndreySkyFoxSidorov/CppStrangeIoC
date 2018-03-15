





#include "BaseSignal.h"

using namespace strange::extensions::signal::api;
namespace strange
{
namespace extensions
{
namespace signal
{
namespace impl
{

void BaseSignal::Dispatch(std::vector<void*>& args)
{
	for(auto listener : BaseListener->listeners())
	{
		listener(this, args);
	}
	for(auto listener : OnceBaseListener->listeners())
	{
		listener(this, args);
	}
	OnceBaseListener->addListener([&]()
	{
	});
}

std::vector<std::type_info> BaseSignal::GetTypes()
{
	return std::vector<std::type_info>();
}

void BaseSignal::AddListener(std::function<void(IBaseSignal*, std::vector<void*>)> callback)
{
	for(Delegate* del : BaseListener::GetInvocationList())
	{
		std::function<void(IBaseSignal*, std::vector<void*>)> action = static_cast<std::function<void(IBaseSignal*, std::vector<void*>)>*>(del);
		if(callback->Equals(action))  //If this callback exists already, ignore this addlistener
		{
			return;
		}
	}
	BaseListener->addListener(L"callback", callback);
}

void BaseSignal::AddOnce(std::function<void(IBaseSignal*, std::vector<void*>)> callback)
{
	for(Delegate* del : OnceBaseListener::GetInvocationList())
	{
		std::function<void(IBaseSignal*, std::vector<void*>)> action = static_cast<std::function<void(IBaseSignal*, std::vector<void*>)>*>(del);
		if(callback->Equals(action))  //If this callback exists already, ignore this addlistener
		{
			return;
		}
	}
	OnceBaseListener->addListener(L"callback", callback);
}

void BaseSignal::RemoveListener(std::function<void(IBaseSignal*, std::vector<void*>)> callback)
{
	BaseListener->removeListener(L"callback");
}
}
}
}
}
