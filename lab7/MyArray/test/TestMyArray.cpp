#include "../MyArray.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Constructors")
{
	SECTION("Default constructor creates empty array")
	{
		MyArray<int> arr;
		REQUIRE(arr.GetSize() == 0);
	}

	SECTION("Copy constructor")
	{
		MyArray<std::string> original;
		original.PushBack("alpha");
		original.PushBack("beta");

		MyArray<std::string> copy(original);

		REQUIRE(copy.GetSize() == 2);
		REQUIRE(copy[0] == "alpha");
		REQUIRE(copy[1] == "beta");

		original[0] = "changed";
		REQUIRE(copy[0] == "alpha");
	}

	SECTION("Move constructor steals")
	{
		MyArray<std::string> original;
		original.PushBack("move");
		size_t oldSize = original.GetSize();

		MyArray<std::string> moved(std::move(original));
		REQUIRE(moved.GetSize() == oldSize);
		REQUIRE(moved[0] == "move");

		REQUIRE(original.GetSize() == 0);
	}
}

TEST_CASE("MyArray functionality")
{
	SECTION("PushBack")
	{
		MyArray<int> arr;
		REQUIRE(arr.GetSize() == 0);

		arr.PushBack(10);
		arr.PushBack(20);
		REQUIRE(arr.GetSize() == 2);
		REQUIRE(arr[0] == 10);
		REQUIRE(arr[1] == 20);
	}

	SECTION("Index operator tout-of-range")
	{
		MyArray<int> arr;
		REQUIRE(arr.GetSize() == 0);

		arr.PushBack(1);
		REQUIRE_THROWS_AS(arr[1], std::out_of_range);
	}

	SECTION("Resize expands")
	{
		MyArray<int> arr;
		REQUIRE(arr.GetSize() == 0);

		arr.PushBack(1);
		arr.Resize(10);
		REQUIRE(arr.GetSize() == 10);
		REQUIRE(arr[5] == 0);
	}

	SECTION("Resize shrinks")
	{
		MyArray<int> arr;

		arr.PushBack(1);
		arr.PushBack(2);
		arr.Resize(1);
		REQUIRE(arr.GetSize() == 1);
	}

	SECTION("Resize to zero")
	{
		MyArray<int> arr;
		arr.PushBack(10);
		arr.PushBack(20);
		arr.Resize(0);

		REQUIRE(arr.GetSize() == 0);
		REQUIRE_THROWS_AS(arr[0], std::out_of_range);
	}

	SECTION("Clear")
	{
		MyArray<int> arr;

		arr.PushBack(42);
		arr.Clear();
		REQUIRE(arr.GetSize() == 0);
		REQUIRE_THROWS_AS(arr[0], std::out_of_range);
	}

	// TODO пустой CLEAR
	SECTION("Clear empty")
	{
		MyArray<int> arr;

		arr.Clear();
		REQUIRE(arr.GetSize() == 0);
		REQUIRE_THROWS_AS(arr[0], std::out_of_range);
	}
}

TEST_CASE("MyArray assignment operators")
{
	SECTION("Copy assignment")
	{
		MyArray<int> a;
		a.PushBack(1);
		a.PushBack(2);
		a.PushBack(3);

		MyArray<int> b;
		b = a;

		REQUIRE(b.GetSize() == 3);
		REQUIRE(b[0] == 1);
		REQUIRE(b[1] == 2);
		REQUIRE(b[2] == 3);

		a[0] = 10;
		REQUIRE(b[0] == 1);
	}

	SECTION("Move assignment")
	{
		MyArray<int> a;
		a.PushBack(5);
		a.PushBack(6);

		MyArray<int> b;
		b = std::move(a);

		REQUIRE(b.GetSize() == 2);
		REQUIRE(b[0] == 5);
		REQUIRE(b[1] == 6);

		REQUIRE(a.GetSize() == 0);
	}

	SECTION("Self-assignment (copy)")
	{
		MyArray<int> a;
		a.PushBack(1);
		a.PushBack(2);

		a = a;
		REQUIRE(a.GetSize() == 2);
		REQUIRE(a[0] == 1);
		REQUIRE(a[1] == 2);
	}

	SECTION("Self-assignment (move)")
	{
		MyArray<int> a;
		a.PushBack(3);
		a.PushBack(4);

		a = std::move(a);
		REQUIRE(a.GetSize() == 2);
		REQUIRE(a[0] == 3);
		REQUIRE(a[1] == 4);
	}

	SECTION("Copy assignment to larger destination")
	{
		MyArray<int> a;
		a.PushBack(1);
		a.PushBack(2);

		MyArray<int> b;
		for (int i = 0; i < 10; ++i)
		{
			b.PushBack(i);
		}
		b = a;

		REQUIRE(b.GetSize() == 2);
		REQUIRE(b[0] == 1);
		REQUIRE(b[1] == 2);
	}

	SECTION("Copy assignment to smaller destination")
	{
		MyArray<int> a;
		for (int i = 0; i < 5; ++i)
			a.PushBack(i);

		MyArray<int> b;
		b.PushBack(99);

		b = a;

		REQUIRE(b.GetSize() == 5);
		for (int i = 0; i < 5; ++i)
		{
			REQUIRE(b[i] == i);
		}
	}
}

TEST_CASE("Iterators")
{
	MyArray<int> arr;
	for (int i = 0; i < 5; i++)
	{
		arr.PushBack(i);
	}

	SECTION("Range-based for")
	{
		int expected = 0;
		for (auto value : arr)
		{
			REQUIRE(value == expected++);
		}
	}

	SECTION("Reverse iteration")
	{
		int expected = 4;
		for (auto it = arr.rbegin(); it != arr.rend(); it++)
		{
			REQUIRE(*it == expected--);
		}
	}

	SECTION("Iterators after resize")
	{
		MyArray<int> arrRes;
		for (int i = 0; i < 5; i++)
		{
			arrRes.PushBack(i);
		}
		arrRes.Resize(3);
		REQUIRE(*arrRes.rbegin() == 2);
	}

	SECTION("STL iterator")
	{
		MyArray<int> arrRes;
		for (int i = 0; i < 5; i++)
		{
			arrRes.PushBack(i);
		}

		REQUIRE(std::find(arrRes.begin(), arrRes.end(), 3));
	}
}

TEST_CASE("Templated assignment")
{
	MyArray<int> intArr;
	intArr.PushBack(1);
	intArr.PushBack(2);

	MyArray<double> doubleArr;
	doubleArr = intArr;

	REQUIRE(doubleArr.GetSize() == 2);
	REQUIRE(doubleArr[0] == 1.0);
	REQUIRE(doubleArr[1] == 2.0);
}

TEST_CASE("Cast test")
{
	struct Man
	{
		std::string name;
		operator int() const
		{
			return std::stoi(name);
		}
	};

	Man man("Andrey");

	MyArray<int> intArr;
	intArr.PushBack(1);
	intArr.PushBack(2);

	MyArray<Man> manArr;
	manArr.PushBack(man);

	REQUIRE_THROWS(intArr = manArr);
}

TEST_CASE("MyArray with strings")
{
	MyArray<std::string> arr;
	arr.PushBack("hello");
	arr.PushBack("world");

	REQUIRE(arr.GetSize() == 2);
	REQUIRE(arr[0] == "hello");
	REQUIRE(arr[1] == "world");

	arr.Resize(3);
	REQUIRE(empty(arr[2]));
}

TEST_CASE("MyArray with floats")
{
	MyArray<float> arr;
	arr.PushBack(3.14);
	arr.PushBack(2.71);

	REQUIRE(arr.GetSize() == 2);
	REQUIRE(fabs(arr[1] - 2.71) < std::numeric_limits<float>::epsilon());
}
