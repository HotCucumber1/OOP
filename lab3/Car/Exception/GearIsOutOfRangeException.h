#pragma once
#include <stdexcept>

class GearIsOutOfRangeException : public std::runtime_error
{
public:
	GearIsOutOfRangeException();
};
