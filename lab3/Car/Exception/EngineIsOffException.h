#pragma once
#include <stdexcept>

class EngineIsOffException : public std::runtime_error
{
public:
	EngineIsOffException();
};
