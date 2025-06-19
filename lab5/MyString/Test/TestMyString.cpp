#include "../Model/MyString.h"
#include <catch2/catch_all.hpp>


TEST_CASE("MyString construction")
{
	SECTION("Default constructor")
	{
		MyString s;
		REQUIRE(s.GetLength() == 0);
		REQUIRE(s.GetStringData() != nullptr);
		REQUIRE(strcmp(s.GetStringData(), "") == 0);
	}

	SECTION("From C-string")
	{
		MyString s("hello");
		REQUIRE(s.GetLength() == 5);
		REQUIRE(strcmp(s.GetStringData(), "hello") == 0);
	}

	SECTION("From C-string with length")
	{
		MyString s("hello world", 5);
		REQUIRE(s.GetLength() == 5);
		REQUIRE(strcmp(s.GetStringData(), "hello") == 0);
	}

	SECTION("From std::string")
	{
		std::string stlStr = "test";
		MyString s(stlStr);
		REQUIRE(s.GetLength() == 4);
		REQUIRE(strcmp(s.GetStringData(), "test") == 0);
	}

	SECTION("Copy construction")
	{
		MyString orig("original");
		MyString copy(orig);
		REQUIRE(copy.GetLength() == orig.GetLength());
		REQUIRE(strcmp(copy.GetStringData(), orig.GetStringData()) == 0);
	}

	SECTION("Move construction")
	{
		MyString orig("movable");
		MyString moved(std::move(orig));
		REQUIRE(moved.GetLength() == 7);
		REQUIRE(orig.GetLength() == 0);
	}
}

TEST_CASE("MyString assignment")
{
	MyString s1("first");
	MyString s2("second");

	SECTION("Copy assignment")
	{
		s1 = s2;
		REQUIRE(strcmp(s1.GetStringData(), "second") == 0);
		REQUIRE(s1.GetLength() == s2.GetLength());
	}

	SECTION("Move assignment")
	{
		MyString s;
		s = std::move(s2);
		REQUIRE(strcmp(s.GetStringData(), "second") == 0);
		REQUIRE(s2.GetLength() == 0);
	}

	SECTION("Self assignment")
	{
		s1 = s1;
		REQUIRE(strcmp(s1.GetStringData(), "first") == 0);
	}
}

TEST_CASE("MyString operations")
{
	SECTION("Concatenation")
	{
		MyString s1("hello");
		MyString s2(" world");
		MyString result = s1 + s2;
		REQUIRE(strcmp(result.GetStringData(), "hello world") == 0);
	}

	SECTION("Append")
	{
		MyString s("hello");
		s += MyString(" world");
		REQUIRE(strcmp(s.GetStringData(), "hello world") == 0);
	}

	SECTION("SubString")
	{
		MyString s("hello world");
		REQUIRE(strcmp(s.SubString(6).GetStringData(), "world") == 0);
		REQUIRE(strcmp(s.SubString(0, 5).GetStringData(), "hello") == 0);
		REQUIRE(s.SubString(100).GetLength() == 0);
	}

	SECTION("Comparison")
	{
		MyString a("apple");
		MyString b("banana");
		REQUIRE(a < b);
		REQUIRE(b > a);
		REQUIRE(a == MyString("apple"));
	}

	SECTION("Stream operations")
	{
		std::ostringstream oss;
		MyString s("output");
		oss << s;
		REQUIRE(oss.str() == "output");

		std::istringstream iss("input");
		MyString input;
		iss >> input;
		REQUIRE(input == MyString("input"));
	}
}

TEST_CASE("MyString element access")
{
	MyString s("hello");

	SECTION("Valid index")
	{
		REQUIRE(s[0] == 'h');
		REQUIRE(s[4] == 'o');
		s[0] = 'H';
		REQUIRE(s[0] == 'H');
	}

	SECTION("Const access")
	{
		const MyString cs("const");
		REQUIRE(cs[0] == 'c');
	}

	SECTION("Out of bounds")
	{
		REQUIRE_THROWS_AS(s[10], std::out_of_range);
	}
}

TEST_CASE("MyString edge cases")
{
	SECTION("Empty string operations")
	{
		MyString empty;
		REQUIRE(empty.GetLength() == 0);
		REQUIRE(empty.GetCapacity() >= 0);
		REQUIRE_NOTHROW(empty.Clear());
	}

	SECTION("Nullptr handling")
	{
		REQUIRE_NOTHROW(MyString(nullptr));
		MyString s(nullptr);
		REQUIRE(s.GetLength() == 0);
	}

	SECTION("Clear method")
	{
		MyString s("to clear");
		s.Clear();
		REQUIRE(s.GetLength() == 0);
		REQUIRE(strcmp(s.GetStringData(), "") == 0);
	}

	SECTION("Move from empty")
	{
		MyString empty;
		MyString moved(std::move(empty));
		REQUIRE(moved.GetLength() == 0);
	}

	SECTION("Self append")
	{
		MyString s("test");
		s += s;
		REQUIRE(strcmp(s.GetStringData(), "testtest") == 0);
	}
}

TEST_CASE("MyString capacity")
{
	SECTION("Capacity growth")
	{
		MyString s;
		auto prevCapacity = s.GetCapacity();
		s += MyString("aa");

		REQUIRE(s.GetCapacity() >= prevCapacity);
	}
}