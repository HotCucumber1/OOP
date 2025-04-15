#pragma once
#include <stdexcept>

class UndeclaredIdentifierException : public std::runtime_error
{
public:
	UndeclaredIdentifierException();
};
