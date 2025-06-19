#include "HttpUrl.h"
#include "../Exception/Exceptions.h"
#include <regex>


HttpUrl::HttpUrl(const std::string& url)
{
	const int protocolPos = 1;
	const int domainPos = 2;
	const int portPos = 3;
	const int documentPos = 4;

	const std::regex urlRegex(
		R"(^(http|https):\/\/([^\s/:\?]+)(?::(6553[0-5]|655[0-2]\d|65[0-4]\d{2}|6[0-4]\d{3}|[1-5]\d{4}|[1-9]\d{0,3}))?(\/[^\s]*)?$)",
		std::regex_constants::icase
	);

	std::smatch urlMatch;
	if (!std::regex_match(url, urlMatch, urlRegex))
	{
		throw UrlParsingError();
	}
	auto portStr = urlMatch[portPos].str();

	m_domain = urlMatch[domainPos].str();
	m_document = urlMatch[documentPos].str();
	m_protocol = GetProtocolFromStr(urlMatch[protocolPos].str());
	m_port = portStr.empty()
		? PORT.at(m_protocol)
		: std::stoi(portStr);

	AssertPortIsCorrect();
}

HttpUrl::HttpUrl(
	std::string domain,
	std::string document,
	Protocol protocol,
	unsigned short port
	)
	: m_domain(std::move(domain))
	, m_document(std::move(document))
	, m_protocol(protocol)
	, m_port(port)
{
	AssertPortIsCorrect();
	if (m_document[0] != '/')
	{
		m_document = '/' + m_document;
	}
}

HttpUrl::HttpUrl(
	std::string domain,
	std::string document,
	Protocol protocol
	)
	: HttpUrl(
		  std::move(domain),
		  std::move(document),
		  protocol,
		  PORT.at(protocol)
		  )
{
}

std::string HttpUrl::GetURL() const
{
	std::string urlStr = GetProtocolStr(m_protocol) + "://" + m_domain;
	if (m_port != PORT.at(m_protocol))
	{
		urlStr += ':' + std::to_string(m_port);
	}
	return urlStr + m_document;
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
	return m_port;
}

void HttpUrl::AssertPortIsCorrect() const
{
	if (m_port == 0)
	{
		throw WrongPortError();
	}
}