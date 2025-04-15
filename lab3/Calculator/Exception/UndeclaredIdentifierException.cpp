#include "UndeclaredIdentifierException.h"


UndeclaredIdentifierException::UndeclaredIdentifierException()
	: std::runtime_error("Name does not exist")
{
}