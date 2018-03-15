#pragma once

#include <stdexcept>

class ContextException : public std::exception
{
private:
	std::string msg;

public:
	ContextException( const std::string& message = "" ) : msg( message )
	{
	}

	const char* what() const throw()
	{
		return msg.c_str();
	}
};
