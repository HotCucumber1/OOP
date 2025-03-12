#include "PrimeGenerator.hpp"
#include "PrimeGeneratorCore.hpp"
#include <algorithm>
#include <stdexcept>

void AssertArgumentNumber(int argc)
{
	const int requiredArgumentNumber = 2;
	if (argc != requiredArgumentNumber)
	{
		throw std::invalid_argument("Wrong argument number");
	}
}

void AssertNumberIsPositive(int n)
{
	if (n < 0)
	{
		throw std::invalid_argument("Number nust be positive");
	}
}

bool IsNumber(const std::string& stringNumber)
{
	return !stringNumber.empty() &&
		std::all_of(stringNumber.begin(), stringNumber.end(), ::isdigit);
}

void AssertArgumentIsNumber(const std::string& string)
{
	if (!IsNumber(string))
	{
		throw std::invalid_argument("Argument is not a number");
	}
}

int GetUpperBoundFromCLI(int argc, char* argv[])
{
	AssertArgumentNumber(argc);
	AssertArgumentIsNumber(argv[1]);
	return std::stoi(argv[1]);
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	AssertNumberIsPositive(upperBound);

	std::set<int> primeNumbers = {};
	std::vector<bool> sieve = GetSieve(upperBound);

	for (int i = 0; i < sieve.size(); i++)
	{
		if (!sieve[i])
		{
			continue;
		}
		primeNumbers.insert(i);
	}
	return primeNumbers;
}

void PrintSet(const std::set<int>& set, std::ostream& output)
{
	for (const auto& number : set)
	{
		output << number << ' ';
	}
	output << std::endl;
}

std::vector<bool> GetSieve(int n)
{
	AssertNumberIsPositive(n);
	std::vector<bool> primeNumbers(n + 1, true);
	primeNumbers[0] = primeNumbers[1] = false;

	for (int i = 2; i <= n; i++)
	{
		if (!primeNumbers[i])
		{
			continue;
		}
		for (int j = 2 * i; j <= n; j += i)
		{
			primeNumbers[j] = false;
		}
	}
	return primeNumbers;
}