#pragma once
#include <stdexcept>

class WrongInputException : public std::runtime_error
{
public:
	WrongInputException();
};