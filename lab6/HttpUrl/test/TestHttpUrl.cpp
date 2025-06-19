#include <catch2/catch_all.hpp>
#include "../Model/HttpUrl.h"
#include "../Exception/Exceptions.h"


TEST_CASE("Constructor without port")
{
	SECTION("Constructor success")
	{
		std::string domain = "domain";
		std::string document = "document";
		Protocol protocol = Protocol::HTTP;
		HttpUrl url(domain, document, protocol);

		REQUIRE(url.GetDomain() == domain);
		REQUIRE(url.GetDocument() == '/' + document);
		REQUIRE(url.GetProtocol() == protocol);
		REQUIRE(url.GetPort() == PORT.at(protocol));
	}

	SECTION("Constructor success")
	{
		std::string domain = "domain";
		std::string document = "document";
		Protocol protocol = Protocol::HTTPS;
		HttpUrl url(domain, document, protocol);

		REQUIRE(url.GetDomain() == domain);
		REQUIRE(url.GetDocument() == '/' + document);
		REQUIRE(url.GetProtocol() == protocol);
		REQUIRE(url.GetPort() == PORT.at(protocol));
	}
}

TEST_CASE("Constructor with port")
{
	SECTION("Constructor with valid port success")
	{
		std::string domain = "domain";
		std::string document = "document";
		Protocol protocol = Protocol::HTTP;
		unsigned short port = 1000;
		HttpUrl url(domain, document, protocol, port);

		REQUIRE(url.GetDomain() == domain);
		REQUIRE(url.GetDocument() == '/' + document);
		REQUIRE(url.GetProtocol() == protocol);
		REQUIRE(url.GetPort() == port);
	}

	SECTION("Constructor with invalid port success")
	{
		std::string domain = "domain";
		std::string document = "document";
		Protocol protocol = Protocol::HTTP;
		unsigned short port = 0;

		REQUIRE_THROWS_AS(HttpUrl(domain, document, protocol, port), WrongPortError);
	}

	SECTION("Get URL success")
	{
		std::string domain = "domain";
		std::string document = "document";
		Protocol protocol = Protocol::HTTP;
		unsigned short port = 1000;
		HttpUrl url(domain, document, protocol, port);

		REQUIRE(url.GetURL() == "http://domain:1000/document");
	}
}

TEST_CASE("Constructor by urlStr")
{
	SECTION("Constructor with valid url")
	{
		const std::string url = "http://example.com:8080/index.html";
		HttpUrl httpUrl(url);
		REQUIRE(httpUrl.GetURL() == url);
	}

	SECTION("Constructor with upper case protocol")
	{
		const std::string url = "HtTp://example.com:8080/index.html";
		HttpUrl httpUrl(url);
		REQUIRE(httpUrl.GetURL() == "http://example.com:8080/index.html");
	}

	SECTION("Constructor with default HTTP port")
	{
		const std::string url = "http://example.com/index.html";
		HttpUrl httpUrl(url);
		REQUIRE(httpUrl.GetPort() == 80);
	}

	SECTION("Constructor with default HTTPS port")
	{
		const std::string url = "https://example.com/index.html";
		HttpUrl httpUrl(url);
		REQUIRE(httpUrl.GetPort() == 443);
	}

	SECTION("Constructor with invalid protocol")
	{
		const std::string url = "htp://example.com:8080/index.html";
		REQUIRE_THROWS_AS(HttpUrl(url), UrlParsingError);
	}

	SECTION("Constructor with invalid port")
	{
		const std::string url = "http://example.com:0/index.html";
		REQUIRE_THROWS_AS(HttpUrl(url), UrlParsingError);
	}

	SECTION("Constructor with empty protocol")
	{
		const std::string url = "example.com:0/index.html";
		REQUIRE_THROWS_AS(HttpUrl(url), UrlParsingError);
	}
}