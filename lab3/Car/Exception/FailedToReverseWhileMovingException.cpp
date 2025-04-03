#include "FailedToReverseWhileMovingException.h"

FailedToReverseWhileMovingException::FailedToReverseWhileMovingException()
	: std::runtime_error("Cannot reverse while moving")
{
}