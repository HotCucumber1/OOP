#include <catch2/catch_all.hpp>
#include "../Model/StringList.h"
#include <iostream>


TEST_CASE("StringList base functions")
{
	StringList list;

	SECTION("Test default constructor")
	{
		REQUIRE(list.IsEmpty());
		REQUIRE(list.GetLength() == 0);
		REQUIRE(list.begin() == list.end());
	}

	SECTION("Test PushBack/PushFront")
	{
		list.PushBack("World");
		list.PushFront("Hello");

		REQUIRE(list.GetLength() == 2);
		REQUIRE(*list.begin() == "Hello");
		REQUIRE(*++list.begin() == "World");
	}
}

TEST_CASE("StringList constructors")
{
	SECTION("Test copy constructor creates independent copy")
	{
		StringList originalList;
		originalList.PushBack("Hello");
		originalList.PushBack("World");

		StringList copy(originalList);

		REQUIRE(copy.GetLength() == 2);
		REQUIRE(*copy.begin() == "Hello");

		REQUIRE(*std::next(copy.begin()) == "World");

		originalList.PushBack("Testing");
		REQUIRE(originalList.GetLength() == 3);
		REQUIRE(copy.GetLength() == 2);
	}

	SECTION("Move constructor transfers ownership")
	{
		StringList sourceList;
		sourceList.PushBack("Test");
		auto oldHead = sourceList.begin();

		StringList moved(std::move(sourceList));

		REQUIRE(moved.GetLength() == 1);
		REQUIRE(*moved.begin() == "Test");
		REQUIRE(moved.begin() == oldHead);

		REQUIRE(sourceList.GetLength() == 0);
		REQUIRE(sourceList.begin() == sourceList.end());
		REQUIRE(sourceList.IsEmpty());
	}
}

TEST_CASE("Assignment operator")
{
	SECTION("Copy assignment makes deep copy")
	{
		StringList list1;
		list1.PushBack("FIRST");
		list1.PushBack("SECOND");

		StringList list2;
		list2.PushBack("X");

		list2 = list1;

		REQUIRE(list2.GetLength() == 2);
		REQUIRE(*list2.begin() == "FIRST");
		REQUIRE(*std::next(list2.begin()) == "SECOND");

		list1.PushBack("C");
		REQUIRE(list1.GetLength() == 3);
		REQUIRE(list2.GetLength() == 2);
	}

	SECTION("Move assignment transfers resources")
	{
		StringList list1;
		list1.PushBack("Move");
		auto oldHead = list1.begin();

		StringList list2;
		list2 = std::move(list1);

		REQUIRE(list2.GetLength() == 1);
		REQUIRE(*list2.begin() == "Move");
		REQUIRE(list2.begin() == oldHead);

		REQUIRE(list1.IsEmpty());
		REQUIRE(list1.GetLength() == 0);
	}

	// TODO self assignement
	SECTION("TestSelfAssignment")
	{
		StringList list;
		list.PushBack("First");
		list.PushBack("Second");
		list.PushBack("Third");

		size_t originalSize = list.GetLength();
		std::string firstElement = *list.begin();

		list = list;

		REQUIRE(list.GetLength() == originalSize);
		REQUIRE(*list.begin() == firstElement);
	}
}

TEST_CASE("Iterators")
{
	StringList list;
	list.PushBack("A");
	list.PushBack("B");
	list.PushBack("C");

	SECTION("Test increment iterator")
	{
		auto it = list.begin();

		REQUIRE(*it == "A");
		++it;
		REQUIRE(*it == "B");
		++it;
		++it;
		REQUIRE(it == list.end());
	}

	SECTION("Test ConstIterator operations")
	{
		const StringList& clist = list;
		auto cit = clist.cbegin();

		REQUIRE(*cit == "A");
	}

	SECTION("Test range-based for loop")
	{
		std::string result;
		for (const auto& s : list)
		{
			result += s;
		}
		REQUIRE(result == "ABC");
	}

	SECTION("Test reverse iterators")
	{
		std::string reverse_result;
		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			reverse_result += *it;
		}
		REQUIRE(reverse_result == "CBA");
	}

	SECTION("Test const reverse iterators")
	{
		const StringList& constList = list;
		std::vector<std::string> reversed(constList.crbegin(), constList.crend());
		REQUIRE((reversed == std::vector<std::string>{"C", "B", "A"}));
	}

	SECTION("Test STL algorithm compatibility")
	{
		auto it = std::find(list.begin(), list.end(), "B");
		REQUIRE(it != list.end());
		REQUIRE(*it == "B");
	}
}

TEST_CASE("Edge cases for iterators")
{
	StringList empty_list;
	StringList single_item;
	single_item.PushBack("X");

	SECTION("Test empty list iteration")
	{
		REQUIRE(empty_list.begin() == empty_list.end());
		REQUIRE(empty_list.rbegin() == empty_list.rend());
	}

	SECTION("Test single item list")
	{
		auto it = single_item.begin();
		REQUIRE(*it == "X");
		REQUIRE(++it == single_item.end());

		auto rit = single_item.rbegin();
		REQUIRE(*rit == "X");
		REQUIRE(++rit == single_item.rend());
	}

	SECTION("Test iterator invalidation")
	{
		StringList list;
		list.PushFront("A");
		auto it = list.begin();
		list.PushFront("Z");
		REQUIRE(*it == "A");
	}
}

TEST_CASE("Insert")
{
	StringList list;
	list.PushBack("A");
	list.PushBack("C");

	SECTION("Insert")
	{
		auto it = std::next(list.begin());
		list.Insert(it, "B");

		REQUIRE(list.GetLength() == 3);
		auto result = std::vector<std::string>(list.begin(), list.end());
		REQUIRE(result == std::vector<std::string>{"A", "B", "C"});
	}
}

TEST_CASE("Erase") {
	StringList list;
	list.PushBack("A");
	list.PushBack("B");
	list.PushBack("C");

	SECTION("Erase middle element")
	{
		auto it = std::next(list.begin());
		list.Erase(it);
		REQUIRE(list.GetLength() == 2);
		REQUIRE(*list.begin() == "A");
		REQUIRE(*std::next(list.begin()) == "C");
	}

	SECTION("Erase first element")
	{
		list.Erase(list.begin());
		REQUIRE(list.GetLength() == 2);
		REQUIRE(*list.begin() == "B");
	}

	SECTION("Erase last element")
	{
		auto it = std::next(list.begin(), 2);
		list.Erase(it);
		REQUIRE(list.GetLength() == 2);
		REQUIRE(*std::prev(list.end()) == "B");
	}

	SECTION("Erase from empty list throws")
	{
		StringList empty;
		REQUIRE_THROWS(empty.Erase(empty.begin()));
	}
}

TEST_CASE("Arithmetic iterators")
{
	StringList list;
	list.PushBack("A");
	list.PushBack("B");
	list.PushBack("C");

	// TODO begin--- or end++
	SECTION("Increment end() iterator")
	{
		auto it = list.end();
		REQUIRE(++it == list.end());
	}

	SECTION("Decrement begin() iterator")
	{
		auto it = list.begin();
		REQUIRE_THROWS(--it);
	}
}