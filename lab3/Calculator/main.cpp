#include "Controller/CalculatorController.h"
#include <iostream>


int main()
{
	try
	{
		Calculator calculator;
		CalculatorController calculatorController{calculator, std::cin, std::cout};
		while (!std::cin.eof() || !std::cin.fail())
		{
			calculatorController.HandleCommand();
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}