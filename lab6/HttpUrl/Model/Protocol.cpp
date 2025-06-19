#include "Protocol.h"
#include "../Exception/Exceptions.h"
#include <algorithm>


std::string ToLower(const std::string& str)
{
	std::string lowerStr = str;

	std::ranges::transform(lowerStr, lowerStr.begin(),[](unsigned char ch) {
		return std::tolower(ch);
	});
	return lowerStr;
}

std::string GetProtocolStr(const Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		return "Unknown protocol";
	}
}

Protocol GetProtocolFromStr(const std::string& protocolStr)
{
	const std::string http = "http";
	const std::string https = "https";

	if (ToLower(protocolStr) == http)
	{
		return Protocol::HTTP;
	}
	if (ToLower(protocolStr) == https)
	{
		return Protocol::HTTPS;
	}
	throw WrongProtocolError();
}