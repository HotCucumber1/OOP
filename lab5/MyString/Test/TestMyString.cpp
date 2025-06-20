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

TEST_CASE("Iterators")
{
	SECTION("Forward")
	{
		MyString str("abc");

		std::string result;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			result += *it;
		}
		REQUIRE(result == "abc");
	}

	SECTION("Reverse iteration")
	{
		MyString str("abc");

		std::string reversed;
		for (auto it = str.rbegin(); it != str.rend(); ++it)
		{
			reversed += *it;
		}

		REQUIRE(reversed == "cba");
	}

	SECTION("Const reverse iteration")
	{
		const MyString str("xyz");

		std::string reversed;
		for (auto it = str.crbegin(); it != str.crend(); ++it)
		{
			reversed += *it;
		}

		REQUIRE(reversed == "zyx");
	}

	SECTION("Iterator arithmetic")
	{
		MyString str("abcdef");

		auto it = str.begin();
		REQUIRE(*(it + 1) == 'b');
		REQUIRE(*(1 + it) == 'b');

		auto end = str.end();

		REQUIRE(it < end);
		REQUIRE(end > it);
	}

	SECTION("Empty string")
	{
		MyString empty;

		REQUIRE(empty.begin() == empty.end());
		REQUIRE(empty.rbegin() == empty.rend());

		std::string result;
		for (auto ch : empty)
		{
			result += ch;
		}
		REQUIRE(result.empty());
	}

	SECTION("Range-based for")
	{
		MyString str("cat");

		std::string result;
		for (auto ch : str)
		{
			result += ch;
		}
		REQUIRE(result == "cat");
	}

	SECTION("Iterator index access")
	{
		MyString str("abcdef");

		auto it = str.begin();
		REQUIRE(it[0] == 'a');
		REQUIRE(it[3] == 'd');

		it[2] = 'Z';
		REQUIRE(str[2] == 'Z');
	}

	SECTION("Const iterator index access")
	{
		const MyString str("abcdef");

		auto it = str.cbegin();
		REQUIRE(it[0] == 'a');
		REQUIRE(it[5] == 'f');
	}

	SECTION("Iterator indexing edge cases")
	{
		MyString str("abc");

		auto it = str.begin();
		REQUIRE(it[0] == 'a');
		REQUIRE(it[2] == 'c');
	}

	SECTION("Iterator update")
	{
		MyString str1("abc");
		MyString str2("def");

		auto it = str1.end();
		REQUIRE(*(--it) == 'c');

		str1 += str2;
		auto it2 = str1.end();
		REQUIRE(*(--it2) == 'f');
	}

	// TODO stl algorithm
	SECTION("STL iterator")
	{
		MyString str1("abcdef");

		REQUIRE(std::find(str1.begin(), str1.end(), 'c'));
	}
}
