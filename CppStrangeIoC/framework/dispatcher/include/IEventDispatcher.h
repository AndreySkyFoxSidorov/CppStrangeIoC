#pragma once

#include "IDispatcher.h"

namespace strange
{
	namespace extensions
	{
		namespace dispatcher
		{
			namespace eventdispatcher
			{
				namespace api
				{
					class IEventDispatcher : public IDispatcher
					{
					public:
						virtual IEventBinding* Bind(void* key) = 0;

						/// Add an observer with exactly one argument to this Dispatcher
						virtual void AddListener(void* evt, EventCallback callback) = 0;

						/// Add an observer with exactly no arguments to this Dispatcher
						virtual void AddListener(void* evt, EmptyCallback callback) = 0;

						/// Remove a previously registered observer with exactly one argument from this Dispatcher
						virtual void RemoveListener(void* evt, EventCallback callback) = 0;

						/// Remove a previously registered observer with exactly no arguments from this Dispatcher
						virtual void RemoveListener(void* evt, EmptyCallback callback) = 0;

						/// Returns true if the provided observer is already registered
						virtual bool HasListener(void* evt, EventCallback callback) = 0;

						/// Returns true if the provided observer is already registered
						virtual bool HasListener(void* evt, EmptyCallback callback) = 0;

						/// By passing true, an observer with exactly one argument will be added to this Dispatcher
						virtual void UpdateListener(bool toAdd, void* evt, EventCallback callback) = 0;

						/// By passing true, an observer with exactly no arguments will be added to this Dispatcher
						virtual void UpdateListener(bool toAdd, void* evt, EmptyCallback callback) = 0;

						/// Allow a previously retained event to be returned to its pool
						virtual void ReleaseEvent(IEvent* evt) = 0;
					};
				}
			}
		}
	}
}

