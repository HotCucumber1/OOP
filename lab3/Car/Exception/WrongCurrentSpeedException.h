#pragma once
#include <stdexcept>

class WrongCurrentSpeedException : public std::runtime_error
{
public:
	WrongCurrentSpeedException();
};
