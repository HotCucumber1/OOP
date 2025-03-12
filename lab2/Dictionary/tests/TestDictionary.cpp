#include "../DictionaryCore.hpp"
#include "../Dictionary.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("Test dictionary format")
{
	SECTION("Correct dictionary format")
	{
		const std::vector<std::string> correctFormat = {"Word1", "Word2"};
		REQUIRE_NOTHROW(AssertValuesNumber(correctFormat));
	}

	SECTION("Wrong dictionary format")
	{
		const std::vector<std::string> wrongFormat = {"Word1"};
		REQUIRE_THROWS_AS(AssertValuesNumber(wrongFormat), std::runtime_error);
	}
}

TEST_CASE("Test add to dictionary")
{
	SECTION("Non existing key")
	{
		Dictionary dictionary = {
			{"key1", {"value1"}},
		};
		const std::string addKey = "key2";
		const std::set<std::string> addValue = {"value2"};

		const Dictionary newDictionary = {
			{"key1", {"value1"}},
			{"key2", {"value2"}},
			{"value2", {"key2"}},
		};
		AddToDict(dictionary, addKey, addValue);
		REQUIRE(dictionary == newDictionary);
	}

	SECTION("Existing key and new value")
	{
		Dictionary dictionary = {
			{"key1", {"value1"}},
		};
		const std::string addKey = "key1";
		const std::set<std::string> addValue = {"value2"};

		const Dictionary newDictionary = {
			{"key1", {"value1", "value2"}},
			{"value2", {"key1"}},
		};
		AddToDict(dictionary, addKey, addValue);
		REQUIRE(dictionary == newDictionary);
	}

	SECTION("Existing key and old value")
	{
		Dictionary dictionary = {
			{"key1", {"value1"}},
		};
		const std::string addKey = "key1";
		const std::set<std::string> addValue = {"value1"};

		const Dictionary newDictionary = {
			{"key1", {"value1"}},
			{"value1", {"key1"}},
		};
		AddToDict(dictionary, addKey, addValue);
		REQUIRE(dictionary == newDictionary);
	}
}

TEST_CASE("Test trim")
{
	SECTION("String with trimmed chars")
	{
		const std::string trimmedString = "String";
		REQUIRE(Trim(trimmedString) == trimmedString);
	}

	SECTION("String with untrimmed chars")
	{
		const std::string untrimmedString = "   String   ";
		const std::string trimmedString = "String";
		REQUIRE(Trim(untrimmedString) == trimmedString);
	}

	SECTION("String with left untrimmed chars")
	{
		const std::string untrimmedString = "   String";
		const std::string trimmedString = "String";
		REQUIRE(Trim(untrimmedString) == trimmedString);
	}

	SECTION("String with right untrimmed chars")
	{
		const std::string untrimmedString = "String    ";
		const std::string trimmedString = "String";
		REQUIRE(Trim(untrimmedString) == trimmedString);
	}

	SECTION("Empty string")
	{
		const std::string emptyString;
		REQUIRE(Trim(emptyString) == emptyString);
	}
}

TEST_CASE("Test split")
{
	SECTION("String with spaces")
	{
		const std::string stringWithSpaces = "string1 string2 string3";
		const std::vector<std::string> splitStrings = {"string1", "string2", "string3"};
		REQUIRE(Split(stringWithSpaces) == splitStrings);
	}

	SECTION("String without spaces")
	{
		const std::string stringWithSpaces = "string1string2string3";
		const std::vector<std::string> splitStrings = {"string1string2string3"};
		REQUIRE(Split(stringWithSpaces) == splitStrings);
	}

	SECTION("Empty string")
	{
		const std::string stringWithSpaces;
		const std::vector<std::string> splitStrings = {};
		REQUIRE(Split(stringWithSpaces) == splitStrings);
	}
}

TEST_CASE("Test get dictionary values")
{
	SECTION("Correct format")
	{
		const std::string string = "key1 : value1";
		const std::pair<std::string, std::string> values = {"key1", "value1"};
		REQUIRE(GetDictValues(string, ':') == values);
	}

	SECTION("Incorrect format")
	{
		const std::string string = "key1 - value1";
		REQUIRE_THROWS_AS(GetDictValues(string, ':'), std::runtime_error);
	}

	SECTION("Empty string")
	{
		const std::string string;
		REQUIRE_THROWS_AS(GetDictValues(string, ':'), std::runtime_error);
	}
}

TEST_CASE("Test to lower")
{
	const std::string upperString = "HELLO WORLD";
	const std::string lowerString = "hello world";
	SECTION("Upper word")
	{
		REQUIRE(ToLower(upperString) == lowerString);
	}

	SECTION("Lower word")
	{
		REQUIRE(ToLower(lowerString) == lowerString);
	}

	SECTION("Empty string")
	{
		REQUIRE(ToLower("").empty());
	}
}

TEST_CASE("Test need to save")
{
	SECTION("Need to save")
	{
		REQUIRE(NeedToSave("y"));
	}

	SECTION("Dont need to save")
	{
		REQUIRE(!NeedToSave("N"));
	}
}

TEST_CASE("Test is value found")
{
	Dictionary dictionary = {
		{"key1", {"value1"}},
	};

	SECTION("Value is found")
	{
		REQUIRE(IsValueFound(dictionary, "key1"));
	}

	SECTION("Value is not found")
	{
		REQUIRE(!IsValueFound(dictionary, "key2"));
	}
}

TEST_CASE("Test get value")
{
	Dictionary dictionary = {
		{"key1", {"value1"}},
	};
	const std::set<std::string> value = {"value1"};

	SECTION("Lower case")
	{
		REQUIRE(GetValue(dictionary, "key1") == value);
	}

	SECTION("Upper case")
	{
		REQUIRE(GetValue(dictionary, "KEY1") == value);
	}
}

TEST_CASE("Test Arguments", "[lw2/Dictionary]")
{
	const char* programName = "./dictionary";
	SECTION("No arguments")
	{
		int argc = 1;
		char* argv[] = { (char*)programName };
		REQUIRE_THROWS_AS(GetFileName(argc, argv), std::invalid_argument);
	}

	SECTION("Filename argument")
	{
		int argc = 2;
		char* argv[] = { (char*)programName, (char*)"dict" };
		REQUIRE(GetFileName(argc, argv) == "dict");
	}

	SECTION("More than one arguments provided")
	{
		int argc = 3;
		char* argv[] = { (char*)programName, (char*)"dict", (char*)"extra_arg" };
		REQUIRE_THROWS_AS(GetFileName(argc, argv), std::invalid_argument);
	}

	SECTION("Empty filename provided")
	{
		int argc = 2;
		char* argv[] = { (char*)programName, (char*)"" };
		REQUIRE(GetFileName(argc, argv).empty());
	}
}


TEST_CASE("Test reading dictionary", "[lw2/Dictionary]")
{
	const std::string emptyFileName = "../../../lab2/Dictionary/tests/empty";
	const std::string notEmptyFileName = "../../../lab2/Dictionary/tests/notEmpty";
	const std::string wrongFormatFileName = "../../../lab2/Dictionary/tests/wrongFormat";

	const Dictionary emptyDict;
	const Dictionary recordDict = {
		{"cat", {"кот", "кошка"}},
		{"кот", {"cat"}},
		{"кошка", {"cat"}}
	};

	SECTION("Empty file name")
	{
		REQUIRE(ReadDict(emptyFileName).empty());
	}

	SECTION("Not empty file name")
	{
		REQUIRE(ReadDict(notEmptyFileName) == recordDict);
	}

	SECTION("Wrong file type")
	{
		REQUIRE_THROWS_AS(ReadDict(wrongFormatFileName), std::runtime_error);
	}
}

