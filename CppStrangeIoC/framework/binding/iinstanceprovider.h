#pragma once
#include <typeinfo>
namespace strange
{
	namespace framework
	{
		namespace api
		{
			class IInstanceProvider
			{

			public:
				template<typename T>
				T GetInstance() = 0;
				virtual void* GetInstance(std::type_info key) = 0;
			};
		}
	}
}

