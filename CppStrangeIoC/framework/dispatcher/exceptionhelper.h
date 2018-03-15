#pragma once

#include <stdexcept>

class InvalidCastException : public std::exception
{
private:
	std::string msg;

public:
	InvalidCastException( const std::string& message = "" ) : msg( message )
	{
	}

	const char* what() const throw()
	{
		return msg.c_str();
	}
};
