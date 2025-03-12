#include "PrimeGenerator.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
	try
	{
		int upperBound = GetUpperBoundFromCLI(argc, argv);
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
		PrintSet(primeNumbers, std::cout);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}