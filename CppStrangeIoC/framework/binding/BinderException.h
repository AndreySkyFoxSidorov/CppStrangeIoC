#pragma once

#include <string>
#include <stdexcept>

#include "Binder.h"
#include "BinderExceptionType.h"
#include "Binding.h"
#include "BindingConst.h"
#include "BindingConstraintType.h"
#include "IBinder.h"
#include "IBinding.h"
#include "IInstanceProvider.h"
#include "IManagedList.h"
#include "ISemiBinding.h"
#include "SemiBinding.h"

using namespace strange::framework::api;
namespace strange
{
	namespace framework
	{
		namespace impl
		{
			class BinderException : public std::exception
			{
			private:
				BinderExceptionType privatetype = static_cast<BinderExceptionType>(0);

			public:
				BinderExceptionType gettype() const;
				void settype(const BinderExceptionType& value);

				BinderException();

				/// Constructs a BinderException with a message and BinderExceptionType
				BinderException(const std::wstring& message, BinderExceptionType exceptionType);
			};
		}
	}
}

