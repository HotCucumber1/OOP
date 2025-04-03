#pragma once
#include <stdexcept>

class UnknownCommandException : public std::runtime_error
{
public:
	UnknownCommandException();
};
