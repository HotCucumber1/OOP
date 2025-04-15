#include "IdentifierIsNotUniqueException.h"


IdentifierIsNotUniqueException::IdentifierIsNotUniqueException()
	: std::runtime_error("Name already exists")
{
}