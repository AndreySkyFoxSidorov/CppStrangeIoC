#pragma once






namespace strange
{
namespace extensions
{
namespace command
{
namespace api
{
class ICommand
{
	/// Override this! `Execute()` is where you place the logic for your Command.
public:
	virtual void Execute() = 0;

	/// Keeps the Command in memory. Use only in conjunction with `Release()`
	virtual void Retain() = 0;

	/// Allows a previous Retained Command to be disposed.
	virtual void Release() = 0;

	/// Inidcates that the Command failed
	/// Used in sequential command groups to terminate the sequence
	virtual void Fail() = 0;

	/// Inform the Command that further Execution has been terminated
	virtual void Cancel() = 0;

	/// Flag to indicate that a pooled Command has been restored to its pristine state.
	/// The CommandBinder will use this to determine if re-Injection is required.
	virtual bool getIsClean() const = 0;
	virtual void setIsClean( const bool& value ) = 0;

	/// The property set by `Retain` and `Release` to indicate whether the Command should be cleaned up on completion of the `Execute()` method.
	virtual bool getretain() const = 0;

	/// The property set to true by a Cancel() call.
	/// Use cancelled internally to determine if further execution is warranted, especially in
	/// asynchronous calls.
	virtual bool getcancelled() const = 0;
	virtual void setcancelled( const bool& value ) = 0;

	/// A payload injected into the Command. Most commonly, this an IEvent.
	virtual void* getdata() const = 0;
	virtual void setdata( void* value ) = 0;

	//The ordered id of this Command, used in sequencing to find the next Command.
	virtual int getsequenceId() const = 0;
	virtual void setsequenceId( const int& value ) = 0;
};
}
}
}
}

