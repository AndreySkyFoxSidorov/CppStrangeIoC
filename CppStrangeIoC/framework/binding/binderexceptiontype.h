#pragma once

namespace strange
{
	namespace framework
	{
		namespace api
		{
			enum class BinderExceptionType
			{
				/// The binder is being used while one or more Bindings are in conflict
				CONFLICT_IN_BINDER
			};
		}
	}
}

