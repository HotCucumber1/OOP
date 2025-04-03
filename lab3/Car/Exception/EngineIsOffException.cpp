#include "EngineIsOffException.h"


EngineIsOffException::EngineIsOffException()
	: std::runtime_error("Сannot set gear while engine is off")
{
}