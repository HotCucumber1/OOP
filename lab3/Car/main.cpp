#include "Controller/CarController.h"
#include <iostream>


int main()
{
	try
	{
		Car car;
		CarController carController(car, std::cin, std::cout);

		while (!std::cin.eof() || !std::cin.fail())
		{
			carController.HandleCommand();
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}