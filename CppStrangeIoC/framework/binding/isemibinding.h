#pragma once
#include "IManagedList.h"

#define Enum void

namespace strange
{
	namespace framework
	{
		namespace api
		{
			class ISemiBinding : public IManagedList
			{

			public:
				virtual Enum* getconstraint() const = 0;
				virtual void setconstraint(Enum* value) = 0;
				virtual bool getuniqueValues() const = 0;
				virtual void setuniqueValues(const bool& value) = 0;
			};
		}
	}
}

