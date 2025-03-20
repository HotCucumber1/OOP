#include "../Dictionary.h"
#include "catch2/catch_all.hpp"


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

TEST_CASE("Test is value found")
{
	Dictionary dictionary = {
		{"key1", {"value1"}},
	};

	SECTION("Value is found")
	{
		REQUIRE(IsTranslationFound(dictionary, "key1"));
	}

	SECTION("Value is not found")
	{
		REQUIRE(!IsTranslationFound(dictionary, "key2"));
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
		REQUIRE(GetTranslation(dictionary, "key1") == value);
	}

	SECTION("Upper case")
	{
		REQUIRE(GetTranslation(dictionary, "KEY1") == value);
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

