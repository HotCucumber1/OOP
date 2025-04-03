#pragma once
#include <stdexcept>

class NegativeSpeedException : public std::runtime_error
{
public:
	NegativeSpeedException();
};
