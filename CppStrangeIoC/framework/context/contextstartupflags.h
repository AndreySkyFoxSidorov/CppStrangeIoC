#pragma once


namespace strange
{
namespace extensions
{
namespace context
{
namespace api
{
// FixiME The following .NET attribute has no direct equivalent in native C++:
// public enum ContextStartupFlags
enum class ContextStartupFlags
{
	/// Context will map bindings and launch automatically (default).
	AUTOMATIC = 0,
	/// Context startup will halt after Core bindings are mapped, but before instantiation or any custom bindings.
	/// If this flag is invoked, the developer must call context.Start()
	MANUAL_MAPPING = 1,
	/// Context startup will halt after all bindings are mapped, but before firing ContextEvent.START (or the analogous Signal).
	/// If this flag is invoked, the developer must call context.Launch()
	MANUAL_LAUNCH = 2,
};
}
}
}
}

