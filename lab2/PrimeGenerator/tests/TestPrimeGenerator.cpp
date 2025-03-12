#include "../PrimeGenerator.hpp"
#include "../PrimeGeneratorCore.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("Test sieve")
{
	SECTION("Positive int")
	{
		const std::vector<bool> sieve = {false, false, true, true, false, true, false, true, false, false, false};
		REQUIRE(GetSieve(10) == sieve);
	}

	SECTION("Negative int")
	{
		REQUIRE_THROWS_AS(GetSieve(-10), std::invalid_argument);
	}

	SECTION("Zero")
	{
		const std::vector<bool> zeroSieve = {false};
		REQUIRE(GetSieve(0) == zeroSieve);
	}
}

TEST_CASE("Test argument number")
{
	SECTION("Correct argument number")
	{
		REQUIRE_NOTHROW(AssertArgumentNumber(2));
	}

	SECTION("Wrong argument number")
	{
		REQUIRE_THROWS_AS(AssertArgumentNumber(3), std::invalid_argument);
	}
}

TEST_CASE("Test argument positivity")
{
	SECTION("Positive argument")
	{
		REQUIRE_NOTHROW(AssertNumberIsPositive(10));
	}

	SECTION("Negative argument")
	{
		REQUIRE_THROWS_AS(AssertArgumentNumber(-10), std::invalid_argument);
	}

	SECTION("Zero argument")
	{
		REQUIRE_THROWS_AS(AssertArgumentNumber(0), std::invalid_argument);
	}
}

TEST_CASE("Test argument is number")
{
	SECTION("Argument is a number")
	{
		REQUIRE(IsNumber("123") == true);
	}

	SECTION("Argument is not a number")
	{
		REQUIRE_NOTHROW(IsNumber("123x") == false);
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
}