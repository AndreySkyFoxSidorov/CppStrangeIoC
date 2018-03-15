#pragma once







#include "IManagedList.h"


namespace strange
{
namespace framework
{
namespace api
{
class ISemiBinding : public IManagedList
{
	/// Set or get the constraint.
public:
	virtual Enum* getconstraint() const = 0;
	virtual void setconstraint( Enum* value ) = 0;

	/// A secondary constraint that ensures that this SemiBinding will never contain multiple values equivalent to each other.
	virtual bool getuniqueValues() const = 0;
	virtual void setuniqueValues( const bool& value ) = 0;
};
}
}
}

