#include "FailedToIncreaseGearException.h"

FailedToIncreaseGearException::FailedToIncreaseGearException()
	: std::runtime_error("Cannot increase gear while moving backward")
{
}