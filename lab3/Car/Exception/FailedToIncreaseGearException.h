#pragma once
#include <stdexcept>

class FailedToIncreaseGearException : public std::runtime_error
{
public:
	FailedToIncreaseGearException();
};
