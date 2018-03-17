#pragma once


namespace strange
{
	namespace extensions
	{
		namespace dispatcher
		{
			namespace api
			{
				class ITriggerable
				{
					/// Cause this ITriggerable to access any provided Key in its Binder by the provided generic and data.
					/// <returns>false if the originator should abort dispatch</returns>
				public:
					template<typename T>
					bool Trigger(void* data) = 0;

					/// Cause this ITriggerable to access any provided Key in its Binder by the provided key and data.
					/// <returns>false if the originator should abort dispatch</returns>
					virtual bool Trigger(void* key, void* data) = 0;
				};
			}
		}
	}
}

