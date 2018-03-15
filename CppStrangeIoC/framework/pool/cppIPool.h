#pragma once







#include "PoolOverflowBehavior.h"
#include "PoolInflationType.h"
#include <typeinfo>


using namespace strange::framework::api;

namespace strange
{
namespace extensions
{
namespace pool
{
namespace api
{
template<typename T>
class IPool : public IPool
{
public:
	virtual T GetInstance() = 0;
};
class IPool : public IManagedList
{
	/// A class that provides instances to the pool when it needs them.
	/// This can be the InjectionBinder, or any class you write that satisfies the IInstanceProvider
	/// interface.
public:
	virtual IInstanceProvider* getinstanceProvider() const = 0;
	virtual void setinstanceProvider( IInstanceProvider* value ) = 0;

	/// The object Type of the first object added to the pool.
	/// Pool objects must be of the same concrete type. This property enforces that requirement.
	virtual std::type_info getpoolType() const = 0;
	virtual void setpoolType( const std::type_info& value ) = 0;

	/// <summary>
	/// Gets an instance from the pool if one is available.
	/// </summary>
	/// <returns>The instance.</returns>
	virtual void* GetInstance() = 0;

	/// <summary>
	/// Returns an instance to the pool.
	/// </summary>
	/// If the instance being released implements IPoolable, the Release() method will be called.
	/// <param name="value">The instance to be return to the pool.</param>
	virtual void ReturnInstance( void* value ) = 0;

	/// <summary>
	/// Remove all instance references from the Pool.
	/// </summary>
	virtual void Clean() = 0;

	/// <summary>
	/// Returns the count of non-committed instances
	/// </summary>
	virtual int getavailable() const = 0;

	/// <summary>
	/// Gets or sets the size of the pool.
	/// </summary>
	/// <value>The pool size. '0' is a special value indicating infinite size. Infinite pools expand as necessary to accomodate requirement.</value>
	virtual int getsize() const = 0;
	virtual void setsize( const int& value ) = 0;

	/// <summary>
	/// Returns the total number of instances currently managed by this pool.
	/// </summary>
	virtual int getinstanceCount() const = 0;

	/// <summary>
	/// Gets or sets the overflow behavior of this pool.
	/// </summary>
	/// <value>A PoolOverflowBehavior value.</value>
	virtual PoolOverflowBehavior getoverflowBehavior() const = 0;
	virtual void setoverflowBehavior( const PoolOverflowBehavior& value ) = 0;

	/// <summary>
	/// Gets or sets the type of inflation for infinite-sized pools.
	/// </summary>
	/// By default, a pool doubles its InstanceCount.
	/// <value>A PoolInflationType value.</value>
	virtual PoolInflationType getinflationType() const = 0;
	virtual void setinflationType( const PoolInflationType& value ) = 0;
};
}
}
}
}

