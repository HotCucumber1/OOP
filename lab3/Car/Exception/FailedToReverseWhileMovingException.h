#pragma once
#include <stdexcept>

class FailedToReverseWhileMovingException : public std::runtime_error
{
public:
	FailedToReverseWhileMovingException();
};
