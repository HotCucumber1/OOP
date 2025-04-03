#include "WrongInputException.h"

WrongInputException::WrongInputException()
	: std::runtime_error("Failed to open input")
{
}