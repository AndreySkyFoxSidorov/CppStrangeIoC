#pragma once





namespace strange
{
namespace extensions
{
namespace dispatcher
{
namespace api
{
class IDispatcher
{
	/// Send a notification of type eventType. No data.
	/// In MVCSContext this dispatches an IEvent.
public:
	virtual void Dispatch( void* eventType ) = 0;

	/// Send a notification of type eventType and the provided data payload.
	/// In MVCSContext this dispatches an IEvent.
	virtual void Dispatch( void* eventType, void* data ) = 0;
};
}
}
}
}

