#pragma once
#include "Protocol.h"

class HttpUrl
{
public:
	explicit HttpUrl(const std::string& url);

	HttpUrl(std::string domain,
			std::string document,
			Protocol protocol = Protocol::HTTP);

	HttpUrl(std::string domain,
			std::string document,
			Protocol protocol,
			unsigned short port);

	std::string GetURL() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	void AssertPortIsCorrect() const;

private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;
};