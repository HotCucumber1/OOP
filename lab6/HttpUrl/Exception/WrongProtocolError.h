#pragma once
#include <stdexcept>

class WrongProtocolError : public std::invalid_argument
{
public:
	WrongProtocolError();
};
