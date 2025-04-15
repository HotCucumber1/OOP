#pragma once
#include <stdexcept>

class InvalidCommandUsageException : public std::runtime_error
{
public:
	InvalidCommandUsageException();
};
