#pragma once







#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <typeinfo>


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
class CommandBinder : public Binder, public ICommandBinder, public IPooledCommandBinder, public ITriggerable
{
private:
	IInjectionBinder* privateinjectionBinder;
	bool privateusePooling = false;

public:
	IInjectionBinder* getinjectionBinder() const;
	void setinjectionBinder( IInjectionBinder* value );

protected:
	std::unordered_map<std::type_info, Pool*> pools;

	/// Tracker for parallel commands in progress
	std::unordered_set<ICommand*> activeCommands;

	/// Tracker for sequences in progress
	std::unordered_map<ICommand*, ICommandBinding*> activeSequences;

public:
	CommandBinder();

	IBinding* GetRawBinding() override;

	virtual void ReactTo( void* trigger );

	virtual void ReactTo( void* trigger, void* data );

protected:
	void next( ICommandBinding* binding, void* data, int depth );

	//EventCommandBinder (and perhaps other sub-classes) use this method to dispose of the data in sequenced commands
	virtual void disposeOfSequencedData( void* data );

	virtual ICommand* invokeCommand( std::type_info cmd, ICommandBinding* binding, void* data, int depth );

	virtual ICommand* createCommand( void* cmd, void* data );

	ICommand* getCommand( std::type_info type );

	void trackCommand( ICommand* command, ICommandBinding* binding );

#if defined(UNITY_EDITOR)
private:
	std::wstring executeCommandOld = L"";
#endif
protected:
	void executeCommand( ICommand* command );

public:
	virtual void Stop( void* key );

	virtual void ReleaseCommand( ICommand* command );

	bool getusePooling() const;
	void setusePooling( const bool& value );

	template<typename T>
	Pool<T>* GetPool();

private:
	void removeSequence( ICommand* command );

public:
	template<typename T>
	bool Trigger( void* data );

	bool Trigger( void* key, void* data );

	template<typename T>
	ICommandBinding* Bind();

	virtual ICommandBinding* Bind( void* value );

protected:
	void resolver( IBinding* binding ) override;

	virtual Pool* makePoolFromType( std::type_info type );

public:
	template<typename T>
	ICommandBinding* GetBinding();
};
}
}
}
}

