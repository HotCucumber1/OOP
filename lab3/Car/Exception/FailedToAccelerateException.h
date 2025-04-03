#pragma once
#include <stdexcept>

class FailedToAccelerateException : public std::runtime_error
{
public:
	FailedToAccelerateException();
};
