#include "../Vector.hpp"
#include "../VectorCore.hpp"
#include "catch2/catch_all.hpp"


TEST_CASE("Test reading")
{
	const std::string emptyInputFile = "../../../lab2/Vector/tests/data/empty";
	const std::string lettersInputFile = "../../../lab2/Vector/tests/data/letters";
	const std::string numbersInputFile = "../../../lab2/Vector/tests/data/numbers";

	const std::vector<double> numbers = {1.01, 2.01, 3.01, 4.01, 5.01};
	const std::vector<double> empty;

	SECTION("Test numbers input")
	{
		std::ifstream input(numbersInputFile);
		REQUIRE(ReadNumbers(input) == numbers);
	}

	SECTION("Test empty input")
	{
		std::ifstream input(emptyInputFile);
		REQUIRE(ReadNumbers(input) == empty);
	}

	SECTION("Test input with letters")
	{
		std::ifstream input(lettersInputFile);
		REQUIRE_THROWS_AS(ReadNumbers(input), std::runtime_error);
	}
}

TEST_CASE("Test process")
{
	const std::vector<double> positiveNumbers = {1.01, 2.01, 3.01, 4.01, 5.01};
	const std::vector<double> negativeNumbers = {-1, 2.01, 3.01, 4.01, 5.01};
	const std::vector<double> zeroNumberData = {1.01, 2.01, 3.01, 4.01, 0};
	const std::vector<double> empty;

	const std::vector<double> expectedPositiveNumbers = {1.0201, 2.0301, 3.0401, 4.0501, 5.0601};
	const std::vector<double> expectedNegativeNumbers = {1, -2.01, -3.01, -4.01, -5.01};
	const std::vector<double> expectedNumbersWithZero = {0, 0, 0, 0, 0};

	SECTION("Test positive numbers")
	{
		REQUIRE(ProcessNumbers(positiveNumbers) == expectedPositiveNumbers);
	}

	SECTION("Test negative numbers")
	{
		REQUIRE(ProcessNumbers(negativeNumbers) == expectedNegativeNumbers);
	}

	SECTION("Test numbers with zero")
	{
		REQUIRE(ProcessNumbers(zeroNumberData) == expectedNumbersWithZero);
	}

	SECTION("Test empty")
	{
		REQUIRE(ProcessNumbers(empty) == empty);
	}
}

TEST_CASE("Test sorting") {

	const std::vector<double> unsortedVector = {1.05, 1.04, 1.03, 1.02, 1.01};
	const std::vector<double> sortedVector = {1.01, 1.02, 1.03, 1.04, 1.05};
	const std::vector<double> emptyVector;

	SECTION("Unsorted vector") {
		REQUIRE(GetSortedNumbers(unsortedVector) == sortedVector);
	}

	SECTION("Sorted vector") {
		REQUIRE(GetSortedNumbers(sortedVector) == sortedVector);
	}

	SECTION("Empty vector") {
		REQUIRE(GetSortedNumbers(emptyVector) == emptyVector);
	}
}