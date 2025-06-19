#include "FindMaxEx.h"
#include <catch2/catch_all.hpp>


struct Man
{
	std::string name;
	int height;
	double weight;
};

auto compareHeight = [](const Man& left, const Man& right) { return left.height < right.height; };
auto compareWeight = [](const Man& left, const Man& right) { return left.weight < right.weight; };

std::vector<Man> men = {
	{"Иванов Иван", 185, 82.3},
	{"Петров Петр", 192, 90.1},
	{"Алексеев Алексей", 178, 75.8},
	{"Дмитриев Дмитрий", 190, 95.4},
	{"Александров Александр", 168, 60.2},
};

const std::string MAX_HEIGHT_MAN = "Петров Петр";
const std::string MAX_WEIGHT_MAN = "Дмитриев Дмитрий";


TEST_CASE("Test")
{
	SECTION("Test empty")
	{
		int max;
		std::vector<int> integers;
		REQUIRE_FALSE(FindMaxEx(integers, max, std::less<int>()));
	}

	SECTION("Test single")
	{
		int max;
		std::vector<int> integers = {1};
		REQUIRE(FindMaxEx(integers, max, std::less<int>()));
		REQUIRE(max == 1);
	}

	SECTION("Test int")
	{
		int max;
		std::vector<int> integers = {1, 2, 3};
		REQUIRE(FindMaxEx(integers, max, std::less<int>()));
		REQUIRE(max == 3);
	}

	SECTION("Test height")
	{
		Man tallest;
		REQUIRE(FindMaxEx(men, tallest, compareHeight));
		REQUIRE(tallest.name == MAX_HEIGHT_MAN);
	}

	SECTION("Test weight")
	{
		Man heaviest;
		REQUIRE(FindMaxEx(men, heaviest, compareWeight));
		REQUIRE(heaviest.name == MAX_WEIGHT_MAN);
	}
}
