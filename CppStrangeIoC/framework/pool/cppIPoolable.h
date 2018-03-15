#pragma once







namespace strange
{
namespace extensions
{
namespace pool
{
namespace api
{
class IPoolable
{
	/// <summary>
	/// Clean up this instance for reuse.
	/// </summary>
	/// Restore methods should clean up the instance sufficiently to remove prior state.
public:
	virtual void Restore() = 0;

	/// <summary>
	/// Keep this instance from being returned to the pool
	/// </summary>
	virtual void Retain() = 0;

	/// <summary>
	/// Release this instance back to the pool.
	/// </summary>
	/// Release methods should clean up the instance sufficiently to remove prior state.
	virtual void Release() = 0;

	/// <summary>
	/// Is this instance retained?
	/// </summary>
	/// <value><c>true</c> if retained; otherwise, <c>false</c>.</value>
	virtual bool getretain() const = 0;
};
}
}
}
}

