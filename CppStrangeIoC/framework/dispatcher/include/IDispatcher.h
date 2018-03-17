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
				public:
					virtual void Dispatch(void* eventType) = 0;
					virtual void Dispatch(void* eventType, void* data) = 0;
				};
			}
		}
	}
}

