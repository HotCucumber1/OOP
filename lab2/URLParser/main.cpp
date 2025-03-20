#include "UrlParser.h"
#include <iostream>


void UrlParser(std::istream& input, std::ostream& output);

int main()
{
	try
	{
		UrlParser(std::cin, std::cout);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}

void UrlParser(std::istream& input, std::ostream& output)
{
	int port;
	Protocol protocol;
	std::string urlString;
	std::string document;
	std::string host;

	while (std::getline(input, urlString))
	{
		if (!ParseURL(urlString, protocol, port, host, document))
		{
			throw std::invalid_argument("Wrong URL is given");
		}
		output << urlString << std::endl
			   << "HOST: " << host << std::endl
			   << "PORT: " << port << std::endl
			   << "DOC: " << document
			   << std::endl;
	}
}