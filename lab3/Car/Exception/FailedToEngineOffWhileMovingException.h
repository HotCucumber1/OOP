#pragma once
#include <stdexcept>

class FailedToEngineOffWhileMovingException : public std::runtime_error
{
public:
	FailedToEngineOffWhileMovingException();
};
