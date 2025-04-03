#pragma once
#include <stdexcept>

class SpeedIsOutOfRangeException : public std::runtime_error
{
public:
	SpeedIsOutOfRangeException();
};
