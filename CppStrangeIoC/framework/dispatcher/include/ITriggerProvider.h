#pragma once
#include "ITriggerable.h"


namespace strange
{
	namespace extensions
	{
		namespace dispatcher
		{
			namespace api
			{
				class ITriggerProvider
				{
					/// Register a Triggerable client with this provider.
				public:
					virtual void AddTriggerable(ITriggerable* target) = 0;

					/// Remove a previously registered Triggerable client from this provider.
					virtual void RemoveTriggerable(ITriggerable* target) = 0;

					/// Count of the current number of trigger clients.
					virtual int getTriggerables() const = 0;
				};
			}
		}
	}
}

