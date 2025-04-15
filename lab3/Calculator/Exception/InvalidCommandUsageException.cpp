#include "InvalidCommandUsageException.h"

InvalidCommandUsageException::InvalidCommandUsageException()
	: std::runtime_error("Invalid usage")
{
}