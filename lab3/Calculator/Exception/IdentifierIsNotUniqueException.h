#pragma once
#include <stdexcept>

class IdentifierIsNotUniqueException : public std::runtime_error
{
public:
	IdentifierIsNotUniqueException();
};
