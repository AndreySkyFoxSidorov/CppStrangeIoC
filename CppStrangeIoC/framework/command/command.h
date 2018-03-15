#pragma once





using namespace strange::extensions::command::api;
using namespace strange::extensions::injector::api;
using namespace strange::framework::api;
using namespace strange::extensions::pool::api;

namespace strange
{
namespace extensions
{
namespace command
{
namespace impl
{
class Command : public ICommand, public IPoolable
{
private:
	ICommandBinder* privatecommandBinder;
	IInjectionBinder* privateinjectionBinder;
	void* privatedata;
	bool privatecancelled = false;
	bool privateIsClean = false;
	int privatesequenceId = 0;
	bool privateretain = false;

	/// Back reference to the CommandBinder that instantiated this Commmand
public:
	ICommandBinder* getcommandBinder() const;
	void setcommandBinder( ICommandBinder* value );

	/// The InjectionBinder for this Context
	IInjectionBinder* getinjectionBinder() const;
	void setinjectionBinder( IInjectionBinder* value );

	void* getdata() const;
	void setdata( void* value );

	bool getcancelled() const;
	void setcancelled( const bool& value );

	bool getIsClean() const;
	void setIsClean( const bool& value );

	int getsequenceId() const;
	void setsequenceId( const int& value );

	Command();

	virtual void Execute();

	virtual void Retain();

	virtual void Release();

	/// Use/override this method to clean up the Command for recycling
	virtual void Restore();

	virtual void Fail();

	void Cancel();

	bool getretain() const;
	void setretain( const bool& value );
};
}
}
}
}

