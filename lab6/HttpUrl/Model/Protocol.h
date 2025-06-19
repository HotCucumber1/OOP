#pragma once
#include <string>
#include <unordered_map>


enum class Protocol
{
	HTTP,
	HTTPS
};

const std::unordered_map<Protocol, unsigned short> PORT = {
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443}
};

std::string GetProtocolStr(Protocol protocol);
Protocol GetProtocolFromStr(const std::string& protocolStr);
