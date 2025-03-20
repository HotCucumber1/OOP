#include "../UrlParser.h"
#include <catch2/catch_all.hpp>


int port;
Protocol protocol;
std::string document;
std::string host;

TEST_CASE("Test protocol")
{
	SECTION("Valid lower case protocol")
	{
		const std::string url = "http://example.com:8080/index.html";
		ParseURL(url, protocol, port, host, document);
		REQUIRE(Protocol::HTTP == protocol);
	}

	SECTION("Valid upper case protocol")
	{
		const std::string url = "hTTpS://example.com:8080/index.html";
		ParseURL(url, protocol, port, host, document);
		REQUIRE(Protocol::HTTPS == protocol);
	}

	SECTION("Invalid protocol")
	{
		const std::string url = "hTpS://example.com:8080/index.html";
		ParseURL(url, protocol, port, host, document);
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}

	SECTION("Empty protocol")
	{
		const std::string url = "example.com:8080/index.html";
		ParseURL(url, protocol, port, host, document);
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
}

TEST_CASE("Test host")
{
	SECTION("Valid host")
	{
		const std::string url = "http://example.com:8080/index.html";
		const std::string urlHost = "example.com";

		ParseURL(url, protocol, port, host, document);
		REQUIRE(urlHost == host);
	}

	SECTION("Empty host")
	{
		const std::string url = "http://:8080/index.html";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}
}

TEST_CASE("Test port")
{
	SECTION("Valid port")
	{
		const std::string url = "http://example.com:8080/index.html";
		const int urlPort = 8080;

		ParseURL(url, protocol, port, host, document);
		REQUIRE(urlPort == port);
	}

	SECTION("Zero port")
	{
		const std::string url = "http://example.com:0/index.html";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}

	SECTION("Too large port")
	{
		const std::string url = "http://example.com:65536/index.html";
		REQUIRE(!ParseURL(url, protocol, port, host, document));
	}

	SECTION("Http port")
	{
		const std::string url = "http://example.com/index.html";
		const int httpPort = 80;

		ParseURL(url, protocol, port, host, document);
		REQUIRE(httpPort == port);
	}

	SECTION("Https port")
	{
		const std::string url = "https://example.com/index.html";
		const int httpPort = 443;

		ParseURL(url, protocol, port, host, document);
		REQUIRE(httpPort == port);
	}

	SECTION("Ftp port")
	{
		const std::string url = "ftp://example.com/index.html";
		const int httpPort = 21;

		ParseURL(url, protocol, port, host, document);
		REQUIRE(httpPort == port);
	}

	SECTION("Non standard https port")
	{
		const std::string url = "https://example.com:8080/index.html";
		const int urlPort = 8080;

		ParseURL(url, protocol, port, host, document);
		REQUIRE(urlPort == port);
	}

	SECTION("Non standard ftp port")
	{
		const std::string url = "ftp://example.com:8080/index.html";
		const int urlPort = 8080;

		ParseURL(url, protocol, port, host, document);
		REQUIRE(urlPort == port);
	}
}

TEST_CASE("Test document")
{
	SECTION("Valid document")
	{
		const std::string url = "ftp://example.com/index.html";
		const std::string urlDocument = "/index.html";

		ParseURL(url, protocol, port, host, document);
		REQUIRE(urlDocument == document);
	}

	SECTION("Empty document")
	{
		const std::string url = "ftp://example.com";

		ParseURL(url, protocol, port, host, document);
		REQUIRE(document.empty());
	}

	SECTION("Document with query params")
	{
		const std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		const std::string urlDocument = "/docs/document1.html?page=30&lang=en#title";

		ParseURL(url, protocol, port, host, document);
		REQUIRE(urlDocument == document);
	}
}