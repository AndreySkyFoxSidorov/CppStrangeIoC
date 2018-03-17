#pragma once

namespace strange
{
	namespace framework
	{
		namespace api
		{
			enum class BindingConst
			{
				/// Null is an acceptable binding, but dictionaries choke on it, so we map null to this instead.
				NULLOID
			};
		}
	}
}

