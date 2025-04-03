#include "FailedToAccelerateException.h"


FailedToAccelerateException::FailedToAccelerateException()
	: std::runtime_error("Cannot accelerate on neutral")
{

}