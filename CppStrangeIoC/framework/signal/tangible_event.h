#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

template<typename T>
class TangibleEvent final
{
private:
	std::unordered_map<std::wstring, T> namedListeners;
public:
	void addListener( const std::wstring& methodName, T namedEventHandlerMethod )
	{
		if( namedListeners.find( methodName ) == namedListeners.end() )
		{
			namedListeners[methodName] = namedEventHandlerMethod;
		}
	}
	void removeListener( const std::wstring& methodName )
	{
		if( namedListeners.find( methodName ) != namedListeners.end() )
		{
			namedListeners.erase( methodName );
		}
	}

private:
	std::vector<T> anonymousListeners;
public:
	void addListener( T unnamedEventHandlerMethod )
	{
		anonymousListeners.push_back( unnamedEventHandlerMethod );
	}

	std::vector<T> listeners()
	{
		std::vector<T> allListeners;
		for( auto listener : namedListeners )
		{
			allListeners.push_back( listener.second );
		}
		allListeners.insert( allListeners.end(), anonymousListeners.begin(), anonymousListeners.end() );
		return allListeners;
	}
};
