#pragma once







#include "BaseSignal.h"
#include <vector>
#include <typeinfo>
#include <functional>
#include "tangible_event.h"


namespace strange
{
namespace extensions
{
namespace signal
{
namespace impl
{
/// Base concrete form for a Signal with no parameters
template<>
class Signal<void, void, void, void> : public BaseSignal
{
public:
	TangibleEvent<System.Action>* Listener = new TangibleEvent<System.Action>();
	TangibleEvent<System.Action>* OnceListener = new TangibleEvent<System.Action>();
	void AddListener( std::function<void()> callback )
	{
		Listener->addListener( L"callback", callback );
	}
	void AddOnce( std::function<void()> callback )
	{
		OnceListener->addListener( L"callback", callback );
	}
	void RemoveListener( std::function<void()> callback )
	{
		Listener->removeListener( L"callback" );
	}
	std::vector<std::type_info> GetTypes() override
	{
		return std::vector<std::type_info>();
	}
	void Dispatch()
	{
		for( auto listener : Listener->listeners() )
		{
			listener();
		}
		for( auto listener : OnceListener->listeners() )
		{
			listener();
		}
		OnceListener->addListener( [&]()
		{
		} );
		BaseSignal::Dispatch( nullptr );
	}
};

/// Base concrete form for a Signal with one parameter
template<typename T>
class Signal<T, void, void, void> : public BaseSignal
{
public:
	TangibleEvent<System.Action<T>>* Listener = new TangibleEvent<System.Action<T>>();
	TangibleEvent<System.Action<T>>* OnceListener = new TangibleEvent<System.Action<T>>();
	void AddListener( std::function<void( T )> callback )
	{
		Listener->addListener( L"callback", callback );
	}
	void AddOnce( std::function<void( T )> callback )
	{
		OnceListener->addListener( L"callback", callback );
	}
	void RemoveListener( std::function<void( T )> callback )
	{
		Listener->removeListener( L"callback" );
	}
	std::vector<std::type_info> GetTypes() override
	{
		std::vector<std::type_info> retv;
		retv.push_back( T::typeid );
		return retv;
	}
	void Dispatch( T type1 )
	{
		for( auto listener : Listener->listeners() )
		{
			listener( type1 );
		}
		for( auto listener : OnceListener->listeners() )
		{
			listener( type1 );
		}
		OnceListener->addListener( [&]()
		{
		} );
		std::vector<void*> outv = {type1};
		BaseSignal::Dispatch( outv );
	}
};

/// Base concrete form for a Signal with two parameters
template<typename T, typename U>
class Signal<T, U, void, void> : public BaseSignal
{
public:
	TangibleEvent<System.Action<T, U>>* Listener = new TangibleEvent<System.Action<T, U>>();
	TangibleEvent<System.Action<T, U>>* OnceListener = new TangibleEvent<System.Action<T, U>>();
	void AddListener( std::function<void( T, U )> callback )
	{
		Listener->addListener( L"callback", callback );
	}
	void AddOnce( std::function<void( T, U )> callback )
	{
		OnceListener->addListener( L"callback", callback );
	}
	void RemoveListener( std::function<void( T, U )> callback )
	{
		Listener->removeListener( L"callback" );
	}
	std::vector<std::type_info> GetTypes() override
	{
		std::vector<std::type_info> retv;
		retv.push_back( T::typeid );
		retv.push_back( U::typeid );
		return retv;
	}
	void Dispatch( T type1, U type2 )
	{
		for( auto listener : Listener->listeners() )
		{
			listener( type1, type2 );
		}
		for( auto listener : OnceListener->listeners() )
		{
			listener( type1, type2 );
		}
		OnceListener->addListener( [&]()
		{
		} );
		std::vector<void*> outv = {type1, type2};
		BaseSignal::Dispatch( outv );
	}
};

/// Base concrete form for a Signal with three parameters
template<typename T, typename U, typename V>
class Signal<T, U, V, void> : public BaseSignal
{
public:
	TangibleEvent<System.Action<T, U, V>>* Listener = new TangibleEvent<System.Action<T, U, V>>();
	TangibleEvent<System.Action<T, U, V>>* OnceListener = new TangibleEvent<System.Action<T, U, V>>();
	void AddListener( std::function<void( T, U, V )> callback )
	{
		Listener->addListener( L"callback", callback );
	}
	void AddOnce( std::function<void( T, U, V )> callback )
	{
		OnceListener->addListener( L"callback", callback );
	}
	void RemoveListener( std::function<void( T, U, V )> callback )
	{
		Listener->removeListener( L"callback" );
	}
	std::vector<std::type_info> GetTypes() override
	{
		std::vector<std::type_info> retv;
		retv.push_back( T::typeid );
		retv.push_back( U::typeid );
		retv.push_back( V::typeid );
		return retv;
	}
	void Dispatch( T type1, U type2, V type3 )
	{
		for( auto listener : Listener->listeners() )
		{
			listener( type1, type2, type3 );
		}
		for( auto listener : OnceListener->listeners() )
		{
			listener( type1, type2, type3 );
		}
		OnceListener->addListener( [&]()
		{
		} );
		std::vector<void*> outv = {type1, type2, type3};
		BaseSignal::Dispatch( outv );
	}
};

/// Base concrete form for a Signal with four parameters
template<typename T, typename U, typename V, typename W>
class Signal : public BaseSignal
{
public:
	TangibleEvent<System.Action<T, U, V, W>>* Listener = new TangibleEvent<System.Action<T, U, V, W>>();
	TangibleEvent<System.Action<T, U, V, W>>* OnceListener = new TangibleEvent<System.Action<T, U, V, W>>();
	void AddListener( std::function<void( T, U, V, W )> callback )
	{
		Listener->addListener( L"callback", callback );
	}
	void AddOnce( std::function<void( T, U, V, W )> callback )
	{
		OnceListener->addListener( L"callback", callback );
	}
	void RemoveListener( std::function<void( T, U, V, W )> callback )
	{
		Listener->removeListener( L"callback" );
	}
	std::vector<std::type_info> GetTypes() override
	{
		std::vector<std::type_info> retv;
		retv.push_back( T::typeid );
		retv.push_back( U::typeid );
		retv.push_back( V::typeid );
		retv.push_back( W::typeid );
		return retv;
	}
	void Dispatch( T type1, U type2, V type3, W type4 )
	{
		for( auto listener : Listener->listeners() )
		{
			listener( type1, type2, type3, type4 );
		}
		for( auto listener : OnceListener->listeners() )
		{
			listener( type1, type2, type3, type4 );
		}
		OnceListener->addListener( [&]()
		{
		} );
		std::vector<void*> outv = {type1, type2, type3, type4};
		BaseSignal::Dispatch( outv );
	}
};

}
}
}
}
