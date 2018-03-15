#pragma once






namespace strange
{
namespace extensions
{
namespace mediation
{
namespace api
{
enum class MediationEvent
{
	/// The View is Awake
	AWAKE,

	/// The View is about to be Destroyed
	DESTROYED,

	/// The View is being Enabled
	ENABLED,

	/// The View is being Disabled
	DISABLED
};
}
}
}
}

