#pragma once
#include <stdexcept>

class InvalidCommandArgumentException : public std::runtime_error
{
public:
	InvalidCommandArgumentException();
};
