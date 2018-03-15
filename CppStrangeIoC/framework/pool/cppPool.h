#pragma once







#include "PoolException.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <typeinfo>


using namespace strange::framework::api;
using namespace strange::extensions::pool::api;

namespace strange
{
namespace extensions
{
namespace pool
{
namespace impl
{
template<typename T>
class Pool : public Pool, public IPool<T>
{
private:
	IInstanceProvider* privateinstanceProvider;
	bool privateuniqueValues = false;
	Enum* privateconstraint;
	std::type_info privatepoolType;
	int privatesize = 0;
	PoolOverflowBehavior privateoverflowBehavior = static_cast<PoolOverflowBehavior>( 0 );
	PoolInflationType privateinflationType = static_cast<PoolInflationType>( 0 );
	bool privateretain = false;

public:
	virtual ~Pool()
	{
		delete instancesAvailable;
	}

	Pool() : Pool()
	{
		setpoolType( T::typeid );
	}

	T GetInstance()
	{
		return static_cast<T>( Pool::GetInstance() );
	}
};

template<>
class Pool<void> : public IPool, public IPoolable
{

public:
	IInstanceProvider* getinstanceProvider() const
	{
		return privateinstanceProvider;
	}
	void setinstanceProvider( IInstanceProvider* value )
	{
		privateinstanceProvider = value;
	}

	/// Stack of instances still in the Pool.
protected:
	System::Collections::Stack* instancesAvailable = new System::Collections::Stack();

	/// A HashSet of the objects checked out of the Pool.
	std::unordered_set<void*> instancesInUse;

	int _instanceCount = 0;

public:
	//StrengeIOC C# -> C++ TODO FIXME: No base class can be determined:
	Pool() : __super()
	{
		setsize( 0 );
		setconstraint( BindingConstraintType::POOL );
		setuniqueValues( true );
		setoverflowBehavior( PoolOverflowBehavior::EXCEPTION );
		setinflationType( PoolInflationType::DOUBLE );
	}

	//	#region IManagedList implementation

	virtual IManagedList* Add( void* value )
	{
		//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
		failIf( value->GetType() != getpoolType(), L"Pool Type mismatch. Pools must consist of a common concrete type.\n\t\tPool type: " + getpoolType().ToString() + L"\n\t\tMismatch type: " + value->GetType()->ToString(), PoolExceptionType::TYPE_MISMATCH );
		_instanceCount++;
		instancesAvailable->Push( value );
		return this;
	}

	virtual IManagedList* Add( std::vector<void*>& list )
	{
		for( auto item : list )
		{
			Add( item );
		}
		return this;
	}

	virtual IManagedList* Remove( void* value )
	{
		_instanceCount--;
		removeInstance( value );
		return this;
	}

	virtual IManagedList* Remove( std::vector<void*>& list )
	{
		for( auto item : list )
		{
			Remove( item );
		}
		return this;
	}

	virtual void* getvalue() const
	{
		return GetInstance();
	}
	//	#endregion

	//	#region ISemiBinding region
	virtual bool getuniqueValues() const
	{
		return privateuniqueValues;
	}
	virtual void setuniqueValues( const bool& value )
	{
		privateuniqueValues = value;
	}
	virtual Enum* getconstraint() const
	{
		return privateconstraint;
	}
	virtual void setconstraint( Enum* value )
	{
		privateconstraint = value;
	}

	//	#endregion

	//	#region IPool implementation

	/// The object Type of the first object added to the pool.
	/// Pool objects must be of the same concrete type. This property enforces that requirement.
	std::type_info getpoolType() const
	{
		return privatepoolType;
	}
	void setpoolType( const std::type_info& value )
	{
		privatepoolType = value;
	}

	int getinstanceCount() const
	{
		return _instanceCount;
	}

	virtual void* GetInstance()
	{
		// Is an instance available?
		if( instancesAvailable->Count > 0 )
		{
			auto retv = instancesAvailable->Pop();
			instancesInUse.insert( retv );
			return retv;
		}
		int instancesToCreate = 0;
		//New fixed-size pool. Populate.
		if( getsize() > 0 )
		{
			if( getinstanceCount() == 0 )
			{
				//New pool. Add instances.
				instancesToCreate = getsize();
			}
			else
			{
				//Illegal overflow. Report and return null
				failIf( getoverflowBehavior() == PoolOverflowBehavior::EXCEPTION, L"A pool has overflowed its limit.\n\t\tPool type: " + getpoolType(), PoolExceptionType::OVERFLOW );
				if( getoverflowBehavior() == PoolOverflowBehavior::WARNING )
				{
					std::wcout << std::endl;
				}
				return nullptr;
			}
		}
		else
		{
			//Zero-sized pools will expand.
			if( getinstanceCount() == 0 || getinflationType() == PoolInflationType::INCREMENT )
			{
				instancesToCreate = 1;
			}
			else
			{
				instancesToCreate = getinstanceCount();
			}
		}
		if( instancesToCreate > 0 )
		{
			failIf( getinstanceProvider() == nullptr, L"A Pool of type: " + getpoolType() + L" has no instance provider.", PoolExceptionType::NO_INSTANCE_PROVIDER );
			for( int a = 0; a < instancesToCreate; a++ )
			{
				auto newInstance = getinstanceProvider()->GetInstance( getpoolType() );
				Add( newInstance );
			}
			return GetInstance();
		}
		//If not, return null
		return nullptr;
	}

	virtual void ReturnInstance( void* value )
	{
		if( std::find( instancesInUse.begin(), instancesInUse.end(), value ) != instancesInUse.end() )
		{
			if( dynamic_cast<IPoolable*>( value ) != nullptr )
			{
				( dynamic_cast<IPoolable*>( value ) )->Restore();
			}
			instancesInUse.Remove( value );
			instancesAvailable->Push( value );
		}
	}

	virtual void Clean()
	{
		instancesAvailable->Clear();
		instancesInUse = std::unordered_set<void*> ();
		_instanceCount = 0;
	}

	virtual int getavailable() const
	{
		return instancesAvailable->Count;
	}

	virtual int getsize() const
	{
		return privatesize;
	}
	virtual void setsize( const int& value )
	{
		privatesize = value;
	}

	virtual PoolOverflowBehavior getoverflowBehavior() const
	{
		return privateoverflowBehavior;
	}
	virtual void setoverflowBehavior( const PoolOverflowBehavior& value )
	{
		privateoverflowBehavior = value;
	}

	virtual PoolInflationType getinflationType() const
	{
		return privateinflationType;
	}
	virtual void setinflationType( const PoolInflationType& value )
	{
		privateinflationType = value;
	}

	//	#endregion

	//	#region IPoolable implementation

	void Restore()
	{
		Clean();
		setsize( 0 );
	}

	void Retain()
	{
		setretain( true );
	}

	void Release()
	{
		setretain( false );
	}


	bool getretain() const
	{
		return privateretain;
	}
	void setretain( const bool& value )
	{
		privateretain = value;
	}

	//	#endregion

	/// <summary>
	/// Permanently removes an instance from the Pool
	/// </summary>
	/// In the event that the removed Instance is in use, it is removed from instancesInUse.
	/// Otherwise, it is presumed inactive, and the next available object is popped from
	/// instancesAvailable.
	/// <param name="value">An instance to remove permanently from the Pool.</param>
protected:
	virtual void removeInstance( void* value )
	{
		//StrengeIOC C# -> C++ TODO FIXME: Need Fix 'ToString':
		failIf( value->GetType() != getpoolType(), L"Attempt to remove a instance from a pool that is of the wrong Type:\n\t\tPool type: " + getpoolType().ToString() + L"\n\t\tInstance type: " + value->GetType()->ToString(), PoolExceptionType::TYPE_MISMATCH );
		if( std::find( instancesInUse.begin(), instancesInUse.end(), value ) != instancesInUse.end() )
		{
			instancesInUse.Remove( value );
		}
		else
		{
			instancesAvailable->Pop();
		}
	}

	void failIf( bool condition, const std::wstring& message, PoolExceptionType type )
	{
		if( condition )
		{
			throw PoolException( message, type );
		}
	}
};
}
}
}
}

