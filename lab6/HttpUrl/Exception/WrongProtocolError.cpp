#include "WrongProtocolError.h"

WrongProtocolError::WrongProtocolError()
	: std::invalid_argument("Wrong protocol")
{
}