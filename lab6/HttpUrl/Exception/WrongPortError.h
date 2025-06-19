#pragma once
#include <stdexcept>

class WrongPortError : public std::invalid_argument
{
public:
	WrongPortError();
};
