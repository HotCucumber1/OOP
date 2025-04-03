#include "UnknownCommandException.h"

UnknownCommandException::UnknownCommandException()
	: std::runtime_error("Unknown command")
{
}