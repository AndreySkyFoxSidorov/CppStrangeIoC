#pragma once







#include <vector>
#include <algorithm>
#include <typeinfo>
#include "exceptionhelper.h"

using namespace strange::extensions::command::api;
using namespace strange::extensions::injector::api;
using namespace strange::framework::api;
using namespace strange::extensions::injector::impl;
using namespace strange::extensions::signal::impl;
using namespace strange::extensions::signal::api;

namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{
class SignalCommandBinder : public CommandBinder
{
public:
	void ResolveBinding( IBinding* binding, void* key ) override;

	void OnRemove() override;

protected:
	ICommand* invokeCommand( std::type_info cmd, ICommandBinding* binding, void* data, int depth ) override;

	/// Create a Command and bind its injectable parameters to the Signal types
	ICommand* createCommandForSignal( std::type_info cmd, void* data, std::vector<std::type_info>& signalTypes );

public:
	template<typename T>
	ICommandBinding* Bind() override;

	/// <summary>Unbind by Signal Type</summary>
	/// <exception cref="InjectionException">If there is no binding for this type.</exception>
	template<typename T>
	void Unbind() override;

	/// <summary>Unbind by Signal Instance</summary>
	/// <param name="key">Instance of IBaseSignal</param>
	void Unbind( void* key, void* name ) override;

	template<typename T>
	ICommandBinding* GetBinding() override;
};
}
}
}
}
