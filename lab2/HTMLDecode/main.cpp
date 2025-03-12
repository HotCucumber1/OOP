#include "Decoder.hpp"
#include <iostream>


int main()
{
	try
	{
		CopyStreamWithHtmlDecode(std::cin, std::cout);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}