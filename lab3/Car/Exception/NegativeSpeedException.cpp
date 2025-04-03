#include "NegativeSpeedException.h"

NegativeSpeedException::NegativeSpeedException()
	: std::runtime_error("Speed cannot be negative")
{
}