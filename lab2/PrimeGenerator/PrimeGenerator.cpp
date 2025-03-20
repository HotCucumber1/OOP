#include "PrimeGenerator.h"
#include <stdexcept>
#include <cmath>


void AssertNumberIsPositive(int n)
{
	if (n < 0)
	{
		throw std::invalid_argument("Number nust be positive");
	}
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	AssertNumberIsPositive(upperBound);

	std::set<int> primeNumbers = {};
	std::vector<bool> sieve = GetSieve(upperBound);

	if (upperBound > 0)
	{
		primeNumbers.insert(2);
	}
	for (int i = 3; i < upperBound; i += 2)
	{
		if (!sieve[i / 2])
		{
			continue;
		}
		primeNumbers.insert(i);
	}
	return primeNumbers;
}

std::vector<bool> GetSieve(int n)
{
	AssertNumberIsPositive(n);
	if (n == 0)
	{
		return {};
	}
	std::vector<bool> primeNumbers((n / 2) + 1, true);

	int upperNumber = static_cast<int>(std::sqrt(n));
	for (int i = 3; i <= upperNumber; i += 2)
	{
		if (!primeNumbers[i / 2])
		{
			continue;
		}
		for (int j = i * i; j < n; j += 2 * i)
		{
			primeNumbers[j / 2] = false;
		}
	}
	return primeNumbers;
}