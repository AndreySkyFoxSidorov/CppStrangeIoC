#pragma once







#include <vector>


using namespace strange::framework::api;

namespace strange
{
namespace framework
{
namespace impl
{
class SemiBinding : public ISemiBinding
{
private:
	Enum* privateconstraint;
	bool privateuniqueValues = false;

protected:
	std::vector<void*> objectValue;

public:
	Enum* getconstraint() const;
	void setconstraint( Enum* value );
	bool getuniqueValues() const;
	void setuniqueValues( const bool& value );

	SemiBinding();

	//	#region IManagedList implementation

	IManagedList* Add( void* o );

	IManagedList* Add( std::vector<void*>& list );

	IManagedList* Remove( void* o );

	IManagedList* Remove( std::vector<void*>& list );
	virtual void* getvalue() const;

	//	#endregion

	/// Remove the value at index splicePos
protected:
	void spliceValueAt( int splicePos );
};
}
}
}

