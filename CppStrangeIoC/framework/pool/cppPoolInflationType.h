#pragma once





namespace strange
{
namespace extensions
{
namespace pool
{
namespace api
{
enum class PoolInflationType
{
	/// When a dynamic pool inflates, add one to the pool.
	INCREMENT,

	/// When a dynamic pool inflates, double the size of the pool
	DOUBLE
};
}
}
}
}

