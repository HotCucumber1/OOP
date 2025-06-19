#include "Model/MyString.h"
#include <iostream>


int main()
{
	try
	{
		MyString str;
		std::cin >> str;
		std::cout << str << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}