#include "UrlParsingError.h"


UrlParsingError::UrlParsingError()
	: std::invalid_argument("Wrong URL")
{
}