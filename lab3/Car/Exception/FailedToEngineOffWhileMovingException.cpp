#include "FailedToEngineOffWhileMovingException.h"

FailedToEngineOffWhileMovingException::FailedToEngineOffWhileMovingException()
	: std::runtime_error("Сar must be stopped and in neutral gear")
{
}
