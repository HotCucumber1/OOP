#include "InvalidCommandArgumentException.h"

InvalidCommandArgumentException::InvalidCommandArgumentException()
	: std::runtime_error("Invalid command argument")
{
}