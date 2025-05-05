#include "Model/Date.h"
#include <iostream>


int main()
{
	try
	{
		Date date;
		std::cin >> date;
		std::cout << date << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}