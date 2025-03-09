#include "../Vector.hpp"
#include "../VectorCore.hpp"
#include "catch2/catch_all.hpp"

const char* programName = "./vector";
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