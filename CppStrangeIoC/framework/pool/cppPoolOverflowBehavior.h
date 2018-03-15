#pragma once






namespace strange
{
namespace extensions
{
namespace pool
{
namespace api
{
enum class PoolOverflowBehavior
{
	/// Requesting more than the fixed size will throw an exception.
	EXCEPTION,

	/// Requesting more than the fixed size will throw a warning.
	WARNING,

	/// Requesting more than the fixed size will return null and not throw an error.
	IGNORE
};
}
}
}
}

