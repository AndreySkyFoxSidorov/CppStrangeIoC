#pragma once





namespace strange
{
namespace extensions
{
namespace context
{
namespace api
{
enum class ContextExceptionType
{
	/// MVCSContext requires a root ContextView
	NO_CONTEXT_VIEW,
	/// MVCSContext requires a mediationBinder
	NO_MEDIATION_BINDER
};
}
}
}
}

