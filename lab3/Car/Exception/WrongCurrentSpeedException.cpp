#include "WrongCurrentSpeedException.h"

WrongCurrentSpeedException::WrongCurrentSpeedException()
	: std::runtime_error("Unsuitable current speed")
{
}