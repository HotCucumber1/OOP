#include "FailedToSetSpeedWhileEngineOffException.h"

FailedToSetSpeedWhileEngineOffException::FailedToSetSpeedWhileEngineOffException()
	: std::runtime_error("Cannot set speed while engine is off")
{
}