#pragma once







#include <vector>



namespace strange
{
namespace framework
{
namespace api
{
class IManagedList
{
	/// Add a value to this List.
public:
	virtual IManagedList* Add( void* value ) = 0;

	/// Add a set of values to this List.
	virtual IManagedList* Add( std::vector<void*>& list ) = 0;

	/// Remove a value from this List.
	virtual IManagedList* Remove( void* value ) = 0;

	/// Remove a set of values from this List.
	virtual IManagedList* Remove( std::vector<void*>& list ) = 0;

	/// Retrieve the value of this List.
	/// If the constraint is MANY, the value will be an Array.
	/// If the constraint is POOL, this becomes a synonym for GetInstance().
	virtual void* getvalue() const = 0;
};
}
}
}

