#include "SpeedIsOutOfRangeException.h"

SpeedIsOutOfRangeException::SpeedIsOutOfRangeException()
	: std::runtime_error("Speed is out of gear range")
{
}