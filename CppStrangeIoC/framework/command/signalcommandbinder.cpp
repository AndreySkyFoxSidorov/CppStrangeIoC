#include "SignalCommandBinder.h"

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

void SignalCommandBinder::ResolveBinding(IBinding* binding, void* key)
{
	CommandBinder::ResolveBinding(binding, key);
	if(bindings->ContainsKey(key))  //If this key already exists, don't bind this again
	{
		IBaseSignal* signal = static_cast<IBaseSignal*>(key);
		signal->AddListener(ReactTo); //Do normal bits, then assign the commandlistener to be reactTo
	}
}

void SignalCommandBinder::OnRemove()
{
	for(auto key : bindings->Keys)
	{
		IBaseSignal* signal = static_cast<IBaseSignal*>(key);
		if(signal != nullptr)
		{
			signal->RemoveListener(ReactTo);
		}
	}
}

ICommand* SignalCommandBinder::invokeCommand(std::type_info cmd, ICommandBinding* binding, void* data, int depth)
{
	IBaseSignal* signal = static_cast<IBaseSignal*>(binding->key);
	ICommand* command = createCommandForSignal(cmd, data, signal->GetTypes()); //Special signal-only command creation
	command->setsequenceId(depth);
	trackCommand(command, binding);
	executeCommand(command);
	return command;
}

ICommand* SignalCommandBinder::createCommandForSignal(std::type_info cmd, void* data, std::vector<std::type_info>& signalTypes)
{
	if(data != nullptr)
	{
		std::vector<void*> signalData = static_cast<std::vector<void*>>(data);
		//Iterate each signal type, in order.
		//Iterate values and find a match
		//If we cannot find a match, throw an error
		std::unordered_set<std::type_info> injectedTypes;
		std::vector<void*> values(signalData);
		for(auto type : signalTypes)
		{
			if(!std::find(injectedTypes.begin(), injectedTypes.end(), type) != injectedTypes.end())  // Do not allow more than one injection of the same Type
			{
				bool foundValue = false;
				for(auto value : values)
				{
					if(value != nullptr)
					{
						if(type.IsAssignableFrom(value->GetType()))  //IsAssignableFrom lets us test interfaces as well
						{
							injectionBinder::Bind(type).ToValue(value).ToInject(false);
							injectedTypes.insert(type);
							values.Remove(value);
							foundValue = true;
							break;
						}
					}
					else //Do not allow null injections
					{
						throw SignalException("SignalCommandBinder attempted to bind a null value from a signal to Command: " + cmd.GetType() + L" to type: " + type, SignalExceptionType::COMMAND_NULL_INJECTION);
					}
				}
				if(!foundValue)
				{
					throw SignalException("Could not find an unused injectable value to inject in to Command: " + cmd.GetType() + L" for Type: " + type, SignalExceptionType::COMMAND_VALUE_NOT_FOUND);
				}
			}
			else
			{
				throw SignalException("SignalCommandBinder: You have attempted to map more than one value of type: " + type + L" in Command: " + cmd.GetType() + L". Only the first value of a type will be injected. You may want to place your values in a VO, instead.", SignalExceptionType::COMMAND_VALUE_CONFLICT);
			}
		}
	}
	ICommand* command = getCommand(cmd);
	command->setdata(data);
	for(auto typeToRemove : signalTypes)  //clean up these bindings
	{
		injectionBinder::Unbind(typeToRemove);
	}
	return command;
}

template<typename T>
ICommandBinding* SignalCommandBinder::Bind()
{
	IInjectionBinding* binding = injectionBinder::GetBinding<T>();
	if(binding == nullptr)  //If this isn't injected yet, inject a new one as a singleton
	{
		injectionBinder::Bind<T>().ToSingleton();
	}
	T signal = static_cast<T>(injectionBinder::GetInstance<T>());
	return CommandBinder::Bind(signal);
}

template<typename T>
void SignalCommandBinder::Unbind()
{
	ICommandBinding* binding = static_cast<ICommandBinding*>(injectionBinder::GetBinding<T>());
	if(binding != nullptr)
	{
		T signal = static_cast<T>(injectionBinder::GetInstance<T>());
		Unbind(signal, nullptr);
	}
}

void SignalCommandBinder::Unbind(void* key, void* name)
{
	if(bindings->ContainsKey(key))
	{
		IBaseSignal* signal = static_cast<IBaseSignal*>(key);
		signal->RemoveListener(ReactTo);
	}
	CommandBinder::Unbind(key, name);
}

template<typename T>
ICommandBinding* SignalCommandBinder::GetBinding()
{
	//This should be a signal, see Bind<T> above
	T signal = static_cast<T>(injectionBinder::GetInstance<T>());
	return dynamic_cast<ICommandBinding*>(CommandBinder::GetBinding(signal));
}
}
}
}
}
