#include "WrongPortError.h"

WrongPortError::WrongPortError()
	: std::invalid_argument("Port must not be equal to zero")
{
}