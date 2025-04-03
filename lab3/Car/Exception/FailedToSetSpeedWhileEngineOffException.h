#pragma once
#include <stdexcept>

class FailedToSetSpeedWhileEngineOffException : public std::runtime_error
{
public:
	FailedToSetSpeedWhileEngineOffException();
};
