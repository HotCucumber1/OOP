#include "UrlParser.h"
#include <regex>
#include <algorithm>


std::string ToLower(const std::string& str)
{
	std::string lowerStr = str;

	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char ch) {
		return tolower(ch);
	});
	return lowerStr;
}

int GetDefaultPortByProtocol(Protocol protocol)
{
	const int httpPort = 80;
	const int httpsPort = 443;
	const int ftpPort = 21;

	switch (protocol)
	{
	case Protocol::HTTP:
		return httpPort;
	case Protocol::HTTPS:
		return httpsPort;
	case Protocol::FTP:
		return ftpPort;
	}
}

Protocol GetProtocol(const std::string& protocolStr)
{
	const std::string http = "http";
	const std::string https = "https";
	const std::string ftp = "ftp";

	if (ToLower(protocolStr) == http)
	{
		return Protocol::HTTP;
	}
	if (ToLower(protocolStr) == https)
	{
		return Protocol::HTTPS;
	}
	if (ToLower(protocolStr) == ftp)
	{
		return Protocol::FTP;
	}
	throw std::invalid_argument("Wrong protocol string");
}

bool ParseURL(const std::string& url, Protocol& protocol,
			  int& port, std::string& host, std::string& document)
{
	const int protocolPos = 1;
	const int hostPos = 2;
	const int portPos = 3;
	const int documentPos = 4;

	const std::regex urlRegex(
		R"(^(http|https|ftp):\/\/([^\s/:\?]+)(?::(6553[0-5]|655[0-2]\d|65[0-4]\d{2}|6[0-4]\d{3}|[1-5]\d{4}|[1-9]\d{0,3}))?(\/[^\s]*)?$)",
		std::regex_constants::icase
	);
	std::smatch urlMatch;
	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		return false;
	}

	auto protocolStr = urlMatch[protocolPos].str();
	auto portStr = urlMatch[portPos].str();
	host = urlMatch[hostPos].str();
	document = urlMatch[documentPos].str();

	try
	{
		protocol = GetProtocol(protocolStr);
	}
	catch (const std::exception&)
	{
		return false;
	}
	port = portStr.empty()
		? GetDefaultPortByProtocol(protocol)
		: std::stoi(portStr);

	return true;
}