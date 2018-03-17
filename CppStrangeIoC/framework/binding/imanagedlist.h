#pragma once
#include <vector>
namespace strange
{
	namespace framework
	{
		namespace api
		{
			class IManagedList
			{
			public:
				virtual IManagedList* Add(void* value) = 0;
				virtual IManagedList* Add(std::vector<void*>& list) = 0;
				virtual IManagedList* Remove(void* value) = 0;
				virtual IManagedList* Remove(std::vector<void*>& list) = 0;
				virtual void* getvalue() const = 0;
			};
		}
	}
}

