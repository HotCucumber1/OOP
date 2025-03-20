#include "../PrimeGenerator.h"
#include "catch2/catch_all.hpp"

TEST_CASE("Test sieve")
{
	SECTION("Positive int")
	{
		const std::vector<bool> sieve = { true, true, true, true, false, true };
		REQUIRE(GetSieve(10) == sieve);
	}

	SECTION("Negative int")
	{
		REQUIRE_THROWS_AS(GetSieve(-10), std::invalid_argument);
	}

	SECTION("Zero")
	{
		const std::vector<bool> zeroSieve = {};
		REQUIRE(GetSieve(0) == zeroSieve);
	}
}

TEST_CASE("Test generate prime numbers set")
{
	SECTION("Positive upper bound")
	{
		const std::set<int> primeNumbers = {2, 3, 5, 7};
		REQUIRE(GeneratePrimeNumbersSet(10) == primeNumbers);
	}

	SECTION("Negative upper bound")
	{
		REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(-10), std::invalid_argument);
	}

	SECTION("Zero upper bound")
	{
		const std::set<int> zeroSieve = {};
		REQUIRE(GeneratePrimeNumbersSet(0) == zeroSieve);
	}

	#ifdef NDEBUG
	SECTION("Test upper bound")
	{
		const int upperBound = 100000000;
		const int primesNumber = 5761455;

		REQUIRE(GeneratePrimeNumbersSet(upperBound).size() == primesNumber);
	}
	#endif
}