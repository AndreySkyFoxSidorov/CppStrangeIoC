#pragma once


#include <vector>
#include <typeinfo>


namespace strange
{
namespace extensions
{
namespace signal
{
namespace api
{
class IBaseSignal
{
	/// Instruct a Signal to call on all its registered listeners
public:
	virtual void Dispatch( std::vector<void*>& args ) = 0;

	/// Attach a callback to this Signal
	/// The callback parameters must match the Types and order which were
	/// originally assigned to the Signal on its creation
	virtual void AddListener( std::function<void( IBaseSignal*, std::vector<void*> )> callback ) = 0;

	/// Attach a callback to this Signal for the duration of exactly one Dispatch
	/// The callback parameters must match the Types and order which were
	/// originally assigned to the Signal on its creation, and the callback
	/// will be removed immediately after the Signal dispatches
	virtual void AddOnce( std::function<void( IBaseSignal*, std::vector<void*> )> callback ) = 0;

	/// Remove a callback from this Signal
	virtual void RemoveListener( std::function<void( IBaseSignal*, std::vector<void*> )> callback ) = 0;

	/// Returns a List<System.Type> representing the Types bindable to this Signal
	virtual std::vector<std::type_info> GetTypes() = 0;
};
}
}
}
}
