#pragma once

#include <stdexcept>

class CommandException : public std::exception
{
private:
	std::string msg;

public:
	CommandException( const std::string& message = "" ) : msg( message )
	{
	}

	const char* what() const throw()
	{
		return msg.c_str();
	}
};

class SignalException : public std::exception
{
private:
	std::string msg;

public:
	SignalException( const std::string& message = "" ) : msg( message )
	{
	}

	const char* what() const throw()
	{
		return msg.c_str();
	}
};
