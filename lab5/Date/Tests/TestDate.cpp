#include "../Model/Date.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Test constructor")
{
	SECTION("Test empty constructor success")
	{
		Date date;

		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
	}

	SECTION("Test timestamp constructor success")
	{
		Date date(365);

		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetYear() == 1971);
		REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
	}

	SECTION("Test min timestamp constructor success")
	{
		Date date(0);

		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetYear() == 1970);
		REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
	}

	SECTION("Test too low timestamp constructor fail")
	{
		REQUIRE_THROWS_AS(Date(-1), std::runtime_error);
	}

	SECTION("Test max timestamp constructor success")
	{
		Date date(2932896);

		REQUIRE(date.GetDay() == 31);
		REQUIRE(date.GetMonth() == Month::DECEMBER);
		REQUIRE(date.GetYear() == 9999);
		REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
	}

	SECTION("Test too large timestamp constructor fail")
	{
		REQUIRE_THROWS_AS(Date(2932897), std::runtime_error);
	}

	SECTION("Test date constructor success")
	{
		const int day = 11;
		const Month month = Month::SEPTEMBER;
		const int year = 2001;
		const WeekDay weekDay = WeekDay::TUESDAY;

		Date date(day, month, year);
		REQUIRE(date.GetDay() == day);
		REQUIRE(date.GetMonth() == month);
		REQUIRE(date.GetYear() == year);
		REQUIRE(date.GetWeekDay() == weekDay);
	}

	SECTION("Test min day success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		REQUIRE(date.GetDay() == day);
	}

	SECTION("Test too low day fail")
	{
		const int day = 0;
		const Month month = Month::JULY;
		const int year = 2005;

		REQUIRE_THROWS_AS(Date(day, month, year), std::runtime_error);
	}

	SECTION("Test max day success")
	{
		const int day = 31;
		const Month month = Month::DECEMBER;
		const int year = 2025;

		Date date(day, month, year);
		REQUIRE(date.GetDay() == day);
	}

	SECTION("Test too large day fail")
	{
		const int day = 32;
		const Month month = Month::JULY;
		const int year = 2005;

		REQUIRE_THROWS_AS(Date(day, month, year), std::runtime_error);
	}

	SECTION("Test too large february day fail")
	{
		const int day = 30;
		const Month month = Month::FEBRUARY;
		const int year = 2005;

		REQUIRE_THROWS_AS(Date(day, month, year), std::runtime_error);
	}

	SECTION("Test leap february day success")
	{
		const int day = 29;
		const Month month = Month::FEBRUARY;
		const int year = 2020;

		Date date(day, month, year);
		REQUIRE(date.GetDay() == day);
	}

	SECTION("Test too large non leap february day fail")
	{
		const int day = 29;
		const Month month = Month::FEBRUARY;
		const int year = 2005;

		REQUIRE_THROWS_AS(Date(day, month, year), std::runtime_error);
	}

	SECTION("Test min year success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 1970;

		Date date(day, month, year);
		REQUIRE(date.GetYear() == year);
	}

	SECTION("Test too low year fail")
	{
		const int day = 0;
		const Month month = Month::JULY;
		const int year = 1969;

		REQUIRE_THROWS_AS(Date(day, month, year), std::runtime_error);
	}

	SECTION("Test max year success")
	{
		const int day = 31;
		const Month month = Month::DECEMBER;
		const int year = 9999;

		Date date(day, month, year);
		REQUIRE(date.GetYear() == year);
	}

	SECTION("Test too large year fail")
	{
		const int day = 32;
		const Month month = Month::JULY;
		const int year = 10000;

		REQUIRE_THROWS_AS(Date(day, month, year), std::runtime_error);
	}
}

TEST_CASE("Test increment")
{
	SECTION("Test prefix success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto nextDay = ++date;
		REQUIRE(nextDay.GetDay() == day + 1);
		REQUIRE(date.GetDay() == day + 1);
	}

	SECTION("Test postfix success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto currDay = date++;
		REQUIRE(currDay.GetDay() == day);
		REQUIRE(date.GetDay() == day + 1);
	}
}

TEST_CASE("Test decrement")
{
	SECTION("Test prefix success")
	{
		const int day = 2;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto lastDay = --date;
		REQUIRE(date.GetDay() == day - 1);
		REQUIRE(lastDay.GetDay() == day - 1);
	}

	SECTION("Test postfix success")
	{
		const int day = 2;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto currDay = date--;
		REQUIRE(date.GetDay() == day - 1);
		REQUIRE(currDay.GetDay() == day);
	}
}

TEST_CASE("Test add")
{
	SECTION("Test add days success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = date + 30;
		REQUIRE(newDate.GetDay() == 31);
	}

	SECTION("Test add date success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = 30 + date;
		REQUIRE(newDate.GetDay() == 31);
	}

	SECTION("Test add with changing month success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = date + 31;
		REQUIRE(newDate.GetMonth() == Month::AUGUST);
	}

	SECTION("Test add with changing year success")
	{
		const int day = 1;
		const Month month = Month::DECEMBER;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = date + 31;
		REQUIRE(newDate.GetYear() == year + 1);
	}

	SECTION("Test add fail")
	{
		const int day = 31;
		const Month month = Month::DECEMBER;
		const int year = 9999;

		Date date(day, month, year);
		REQUIRE_THROWS_AS(date + 1, std::runtime_error);
	}
}

TEST_CASE("Test sub")
{
	SECTION("Test sub days success")
	{
		const int day = 3;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = date - 2;
		REQUIRE(newDate.GetDay() == 1);
	}

	SECTION("Test sub date success")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);

		const int day2 = 5;
		const Month month2 = Month::JULY;
		const int year2 = 2005;
		Date date2(day2, month2, year2);

		auto daysDiff = date2 - date1;
		REQUIRE(daysDiff == 4);
	}

	SECTION("Test sub with changing month success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = date - 1;
		REQUIRE(newDate.GetMonth() == Month::JUNE);
	}

	SECTION("Test sub with changing year success")
	{
		const int day = 1;
		const Month month = Month::JANUARY;
		const int year = 2005;

		Date date(day, month, year);
		auto newDate = date - 1;
		REQUIRE(newDate.GetYear() == year - 1);
	}

	SECTION("Test sub fail")
	{
		const int day = 1;
		const Month month = Month::JANUARY;
		const int year = 1970;

		Date date(day, month, year);
		REQUIRE_THROWS_AS(date - 1, std::runtime_error);
	}

	SECTION("Test sub date with negative result success")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);

		const int day2 = 5;
		const Month month2 = Month::JULY;
		const int year2 = 2005;
		Date date2(day2, month2, year2);

		auto daysDiff = date1 - date2;
		REQUIRE(daysDiff == -4);
	}
}

TEST_CASE("Test add with assignment")
{
	SECTION("Test add days success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		date += 30;
		REQUIRE(date.GetDay() == 31);
	}

	SECTION("Test add with changing month success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		date += 31;
		REQUIRE(date.GetMonth() == Month::AUGUST);
	}

	SECTION("Test add with changing year success")
	{
		const int day = 1;
		const Month month = Month::DECEMBER;
		const int year = 2005;

		Date date(day, month, year);
		date += 31;
		REQUIRE(date.GetYear() == year + 1);
	}

	SECTION("Test add fail")
	{
		const int day = 31;
		const Month month = Month::DECEMBER;
		const int year = 9999;

		Date date(day, month, year);
		REQUIRE_THROWS_AS(date += 1, std::runtime_error);
	}
}

TEST_CASE("Test sub with assignment")
{
	SECTION("Test sub days success")
	{
		const int day = 3;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		date -= 2;
		REQUIRE(date.GetDay() == 1);
	}

	SECTION("Test sub with changing month success")
	{
		const int day = 1;
		const Month month = Month::JULY;
		const int year = 2005;

		Date date(day, month, year);
		date -= 1;
		REQUIRE(date.GetMonth() == Month::JUNE);
	}

	SECTION("Test sub with changing year success")
	{
		const int day = 1;
		const Month month = Month::JANUARY;
		const int year = 2005;

		Date date(day, month, year);
		date -= 1;
		REQUIRE(date.GetYear() == year - 1);
	}

	SECTION("Test sub fail")
	{
		const int day = 1;
		const Month month = Month::JANUARY;
		const int year = 1970;

		Date date(day, month, year);
		REQUIRE_THROWS_AS(date -= 1, std::runtime_error);
	}
}

TEST_CASE("Test equality operator")
{
	SECTION("Test equal")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(date1 == date2);
	}

	SECTION("Test not equal")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1 + 1, month1, year1);

		REQUIRE(!(date1 == date2));
	}
}

TEST_CASE("Test non equality operator")
{
	SECTION("Test non equal")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1 + 1, month1, year1);

		REQUIRE(date1 != date2);
	}

	SECTION("Test equal")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(!(date1 != date2));
	}
}

TEST_CASE("Test more operator")
{
	SECTION("Test more")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1 + 1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(date1 > date2);
	}

	SECTION("Test not more")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(!(date1 > date2));
	}
}

TEST_CASE("Test less operator")
{
	SECTION("Test less")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1 + 1, month1, year1);

		REQUIRE(date1 < date2);
	}

	SECTION("Test not less")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(!(date1 < date2));
	}
}

TEST_CASE("Test more or equal operator")
{
	SECTION("Test more")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1 + 1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(date1 >= date2);
	}

	SECTION("Test not more")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1 + 1, month1, year1);

		REQUIRE(!(date1 >= date2));
	}

	SECTION("Test equal")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(date1 >= date2);
	}
}

TEST_CASE("Test less or equal operator")
{
	SECTION("Test less")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1 + 1, month1, year1);

		REQUIRE(date1 <= date2);
	}

	SECTION("Test not less")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1 + 1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(!(date1 <= date2));
	}

	SECTION("Test equal")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);
		Date date2(day1, month1, year1);

		REQUIRE(date1 <= date2);
	}
}

TEST_CASE("Test output operator")
{
	SECTION("Test print day and month with zero")
	{
		const int day1 = 1;
		const Month month1 = Month::JULY;
		const int year1 = 2005;
		Date date1(day1, month1, year1);

		std::ostringstream output;
		output << date1;

		REQUIRE(output.str() == "01.07.2005");
	}

	SECTION("Test print day and month without zero")
	{
		const int day1 = 11;
		const Month month1 = Month::NOVEMBER;
		const int year1 = 2005;
		Date date1(day1, month1, year1);

		std::ostringstream output;
		output << date1;

		REQUIRE(output.str() == "11.11.2005");
	}
}

TEST_CASE("Test input operator")
{
	SECTION("Test valid input format")
	{
		Date date;
		std::istringstream iss("01.07.2005");

		iss >> date;
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::JULY);
		REQUIRE(date.GetYear() == 2005);
		REQUIRE(date.GetWeekDay() == WeekDay::FRIDAY);
	}

	SECTION("Test invalid input format")
	{
		Date date;
		std::istringstream iss("101.07.2005");

		REQUIRE_THROWS_AS(iss >> date, std::runtime_error);
	}
}