#include "BinderException.h"

using namespace strange::framework::api;
namespace strange
{
	namespace framework
	{
		namespace impl
		{

			BinderExceptionType BinderException::gettype() const
			{
				return privatetype;
			}

			void BinderException::settype(const BinderExceptionType& value)
			{
				privatetype = value;
			}

			BinderException::BinderException() : Exception()
			{
			}

			BinderException::BinderException(const std::wstring& message, BinderExceptionType exceptionType) : Exception(message)
			{
				settype(exceptionType);
			}
		}
	}
}
