#include "../Dictionary.hpp"
#include "catch2/catch_all.hpp"

const char* programName = "./dictionary";
TEST_CASE("Test Arguments", "[lw2/Dictionary]") {

	SECTION("No arguments") {
		int argc = 1;
		char* argv[] = { (char*)programName };
		REQUIRE_THROWS_AS(GetFileName(argc, argv), std::invalid_argument);
	}

	SECTION("Filename argument") {
		int argc = 2;
		char* argv[] = { (char*)programName, (char*)"dict" };
		REQUIRE(GetFileName(argc, argv) == "dict");
	}

	SECTION("More than one arguments provided") {
		int argc = 3;
		char* argv[] = { (char*)programName, (char*)"dict", (char*)"extra_arg" };
		REQUIRE_THROWS_AS(GetFileName(argc, argv), std::invalid_argument);
	}

	SECTION("Empty filename provided") {
		int argc = 2;
		char* argv[] = { (char*)programName, (char*)"" };
		REQUIRE(GetFileName(argc, argv).empty());
	}
}


TEST_CASE("Test reading dictionary", "[lw2/Dictionary]") {
	const std::string emptyFileName = "../../../lab2/Dictionary/tests/empty";
	const std::string notEmptyFileName = "../../../lab2/Dictionary/tests/notEmpty";
	const std::string wrongFormatFileName = "../../../lab2/Dictionary/tests/wrongFormat";

	const Dictionary emptyDict;
	const Dictionary recordDict = {
		{"cat", {"кот", "кошка"}},
		{"кот", {"cat"}},
		{"кошка", {"cat"}}
	};

	SECTION("Empty file name") {
		REQUIRE(ReadDict(emptyFileName).empty());
	}

	SECTION("Not empty file name") {
		REQUIRE(ReadDict(notEmptyFileName) == recordDict);
	}

	SECTION("Wrong file type") {
		REQUIRE_THROWS_AS(ReadDict(wrongFormatFileName), std::runtime_error);
	}
}

