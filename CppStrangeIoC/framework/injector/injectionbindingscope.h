#pragma once





namespace strange
{
namespace extensions
{
namespace injector
{
namespace api
{
enum class InjectionBindingScope
{
	/// Scope is limited to the current Context
	SINGLE_CONTEXT,
	/// Scope is mapped across all Contexts
	CROSS_CONTEXT,
};
}
}
}
}
