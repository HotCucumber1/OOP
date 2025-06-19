#include "Model/HttpUrl.h"
#include <iostream>

void ProcessUrlInfo(std::istream& input, std::ostream& output);
void PrintUtlInfo(const HttpUrl& url, std::ostream& output = std::cout);


int main()
{
	try
	{
		ProcessUrlInfo(std::cin, std::cout);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}


void ProcessUrlInfo(std::istream& input, std::ostream& output)
{
	std::string urlStr;
	while (input >> urlStr)
	{
		try
		{
			HttpUrl url(urlStr);
			PrintUtlInfo(url, output);
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what() << std::endl;
		}
	}
}

void PrintUtlInfo(const HttpUrl& url, std::ostream& output)
{
	output << "Protocol: " << GetProtocolStr(url.GetProtocol()) << '\n'
		   << "Domain: " << url.GetDomain() << '\n'
		   << "Port: " << url.GetPort() << '\n'
		   << "Document: "	<< url.GetDocument() << '\n';
}
