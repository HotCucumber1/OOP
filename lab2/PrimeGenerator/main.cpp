#include "PrimeGenerator.h"
#include <iostream>
#include <algorithm>
#include <ranges>


int GetUpperBoundFromCLI(int argc, char* argv[]);
void AssertArgumentNumber(int argc);
void AssertArgumentIsNumber(const std::string& string);
void PrintSet(const std::set<int>& set, std::ostream& output);

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

int GetUpperBoundFromCLI(int argc, char* argv[])
{
	AssertArgumentNumber(argc);
	AssertArgumentIsNumber(argv[1]);
	return std::stoi(argv[1]);
}

void AssertArgumentNumber(int argc)
{
	const int requiredArgumentNumber = 2;
	if (argc != requiredArgumentNumber)
	{
		throw std::invalid_argument("Wrong argument number");
	}
}

bool IsNumber(const std::string& stringNumber)
{
	return !stringNumber.empty() && std::ranges::all_of(stringNumber, ::isdigit);
}

void AssertArgumentIsNumber(const std::string& string)
{
	if (!IsNumber(string))
	{
		throw std::invalid_argument("Argument is not a number");
	}
}

void PrintSet(const std::set<int>& set, std::ostream& output)
{
	for (const auto& number : set)
	{
		output << number << ' ';
	}
	output << std::endl;
}