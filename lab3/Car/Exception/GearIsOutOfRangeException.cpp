#include "GearIsOutOfRangeException.h"


GearIsOutOfRangeException::GearIsOutOfRangeException()
	: std::runtime_error("Invalid gear")
{
}