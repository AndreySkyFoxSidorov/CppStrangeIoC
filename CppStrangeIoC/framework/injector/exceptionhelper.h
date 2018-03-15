#pragma once

#include <stdexcept>

class InjectionException : public std::exception
{
private:
	std::string msg;

public:
	InjectionException( const std::string& message = "" ) : msg( message )
	{
	}

	const char* what() const throw()
	{
		return msg.c_str();
	}
};
