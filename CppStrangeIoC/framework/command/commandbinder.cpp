#include "CommandBinder.h"
#include "CommandBinding.h"
#include "CommandException.h"

using namespace strange::extensions::command::api;
using namespace strange::extensions::dispatcher::api;
using namespace strange::extensions::injector::api;
using namespace strange::extensions::pool::impl;
using namespace strange::framework::api;
using namespace strange::framework::impl;
using namespace strange::extensions::pool::api;
namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{

IInjectionBinder* CommandBinder::getinjectionBinder() const
{
	return privateinjectionBinder;
}

void CommandBinder::setinjectionBinder(IInjectionBinder* value)
{
	privateinjectionBinder = value;
}

CommandBinder::CommandBinder()
{
	setusePooling(true);
}

IBinding* CommandBinder::GetRawBinding()
{
	return new CommandBinding(resolver);
}

void CommandBinder::ReactTo(void* trigger)
{
	ReactTo(trigger, nullptr);
}

void CommandBinder::ReactTo(void* trigger, void* data)
{
	if(dynamic_cast<IPoolable*>(data) != nullptr)
	{
		(dynamic_cast<IPoolable*>(data))->Retain();
	}
	ICommandBinding* binding = dynamic_cast<ICommandBinding*>(GetBinding(trigger));
	if(binding != nullptr)
	{
		if(binding->isSequence)
		{
			next(binding, data, 0);
		}
		else
		{
			std::vector<void*> values = dynamic_cast<std::vector<void*>>(binding->value);
			int aa = values.size() + 1;
			for(int a = 0; a < aa; a++)
			{
				next(binding, data, a);
			}
		}
	}
}

void CommandBinder::next(ICommandBinding* binding, void* data, int depth)
{
	std::vector<void*> values = dynamic_cast<std::vector<void*>>(binding->value);
	if(values.size() > 0 && depth < values.size())
	{
		std::type_info cmd = dynamic_cast<std::type_info>(values [depth]);
		ICommand* command = invokeCommand(cmd, binding, data, depth);
		ReleaseCommand(command);
	}
	else
	{
		disposeOfSequencedData(data);
		if(binding->isOneOff)
		{
			Unbind(binding);
		}
	}
}

void CommandBinder::disposeOfSequencedData(void* data)
{
	//No-op. Override if necessary.
}

ICommand* CommandBinder::invokeCommand(std::type_info cmd, ICommandBinding* binding, void* data, int depth)
{
	ICommand* command = createCommand(cmd, data);
	command->sequenceId = depth;
	trackCommand(command, binding);
	executeCommand(command);
	return command;
}

ICommand* CommandBinder::createCommand(void* cmd, void* data)
{
	ICommand* command = getCommand(dynamic_cast<std::type_info>(cmd));
	if(command == nullptr)
	{
		std::wstring msg = L"A Command ";
		if(data != nullptr)
		{
			//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
			msg += L"tied to data " + data->ToString();
		}
		msg += L" could not be instantiated.\nThis might be caused by a null pointer during instantiation or failing to override Execute (generally you shouldn't have constructor code in Commands).";
		throw CommandException(msg, CommandExceptionType::BAD_CONSTRUCTOR);
	}
	command->data = data;
	return command;
}

ICommand* CommandBinder::getCommand(std::type_info type)
{
	if(getusePooling() && pools.find(type) != pools.end())
	{
		Pool* pool = pools [type];
		ICommand* command = dynamic_cast<ICommand*>(pool->GetInstance());
		if(command->IsClean)
		{
			getinjectionBinder()->injector.Inject(command);
			command->IsClean = false;
		}
		return command;
	}
	else
	{
		getinjectionBinder()->Bind<ICommand*> ().To(type);
		ICommand* command = getinjectionBinder()->GetInstance<ICommand*> ();
		getinjectionBinder()->Unbind<ICommand*> ();
		return command;
	}
}

void CommandBinder::trackCommand(ICommand* command, ICommandBinding* binding)
{
	if(binding->isSequence)
	{
		activeSequences.emplace(command, binding);
	}
	else
	{
		activeCommands.insert(command);
	}
}

void CommandBinder::executeCommand(ICommand* command)
{
	if(command == nullptr)
	{
		return;
	}
	command->Execute();
}

void CommandBinder::Stop(void* key)
{
	if(dynamic_cast<ICommand*>(key) != nullptr && activeSequences.find(dynamic_cast<ICommand*>(key)) != activeSequences.end())
	{
		removeSequence(dynamic_cast<ICommand*>(key));
	}
	else
	{
		ICommandBinding* binding = dynamic_cast<ICommandBinding*>(GetBinding(key));
		if(binding != nullptr)
		{
			if(activeSequences.ContainsValue(binding))
			{
				for(auto sequence : activeSequences)
				{
					if(sequence.second == binding)
					{
						ICommand* command = sequence.first;
						removeSequence(command);
					}
				}
			}
		}
	}
}

void CommandBinder::ReleaseCommand(ICommand* command)
{
	if(command->retain == false)
	{
		std::type_info t = command->GetType();
		if(getusePooling() && pools.find(t) != pools.end())
		{
			pools [t]->ReturnInstance(command);
		}
		if(std::find(activeCommands.begin(), activeCommands.end(), command) != activeCommands.end())
		{
			activeCommands.Remove(command);
		}
		else if(activeSequences.find(command) != activeSequences.end())
		{
			ICommandBinding* binding = activeSequences [command];
			auto data = command->data;
			activeSequences.erase(command);
			next(binding, data, command->sequenceId + 1);
		}
	}
}

bool CommandBinder::getusePooling() const
{
	return privateusePooling;
}

void CommandBinder::setusePooling(const bool& value)
{
	privateusePooling = value;
}

template<typename T>
Pool<T>* CommandBinder::GetPool()
{
	std::type_info t = T::typeid;
	if(pools.find(dynamic_cast<std::type_info>(t)) != pools.end())
	{
		return dynamic_cast<Pool<T>*>(pools[t]);
	}
	return nullptr;
}

void CommandBinder::removeSequence(ICommand* command)
{
	if(activeSequences.find(command) != activeSequences.end())
	{
		command->Cancel();
		activeSequences.erase(command);
	}
}

template<typename T>
bool CommandBinder::Trigger(void* data)
{
	return Trigger(T::typeid, data);
}

bool CommandBinder::Trigger(void* key, void* data)
{
	ReactTo(key, data);
	return true;
}

template<typename T>
ICommandBinding* CommandBinder::Bind()
{
	return dynamic_cast<ICommandBinding*>(Binder::Bind<T>());
}

ICommandBinding* CommandBinder::Bind(void* value)
{
	return dynamic_cast<ICommandBinding*>(Binder::Bind(value));
}

void CommandBinder::resolver(IBinding* binding)
{
	Binder::resolver(binding);
	if(getusePooling() && (dynamic_cast<ICommandBinding*>(binding))->isPooled)
	{
		if(binding->value != nullptr)
		{
			std::vector<void*> values = dynamic_cast<std::vector<void*>>(binding->value);
			for(auto value : values)
			{
				if(pools.find(value) != pools.end() == false)
				{
					auto myPool = makePoolFromType(value);
					pools [value] = myPool;
				}
			}
		}
	}
}

Pool* CommandBinder::makePoolFromType(std::type_info type)
{
	std::type_info poolType = Pool<*>::typeid->MakeGenericType(type);
	getinjectionBinder()->Bind(type).To(type);
	getinjectionBinder()->Bind<Pool*>().To(poolType).ToName(CommandKeys::COMMAND_POOL);
	Pool* pool = dynamic_cast<Pool*>(getinjectionBinder()->GetInstance<Pool*> (CommandKeys::COMMAND_POOL));
	getinjectionBinder()->Unbind<Pool*> (CommandKeys::COMMAND_POOL);
	return pool;
}

template<typename T>
ICommandBinding* CommandBinder::GetBinding()
{
	return dynamic_cast<ICommandBinding*>(Binder::GetBinding<T>());
}
}
}
}
}
