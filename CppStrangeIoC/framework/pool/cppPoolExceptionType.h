#pragma once





namespace strange
{
namespace extensions
{
namespace pool
{
namespace api
{
enum class PoolExceptionType
{

	/// POOL HAS OVERFLOWED ITS LIMIT
	OVERFLOW,

	/// ATTEMPT TO ADD AN INSTANCE OF DIFFERENT TYPE TO A POOL
	TYPE_MISMATCH,

	/// A POOL HAS NO INSTANCE PROVIDER
	NO_INSTANCE_PROVIDER,
};
}
}
}
}

