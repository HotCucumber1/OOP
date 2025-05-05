#include "Date.h"
#include <tuple>

const int SHIFT = 719468;
const int ERA_PERIOD = 400;
const int YEAR = 365;
const int CENTURY = 100;
const int ERA_DAYS = 146097;
const int MAX_ERA_DAY = ERA_DAYS - 1;

const int MAX_TIMESTAMP = 2932896;

const int MIN_DAY = 1;
const int MAX_DAY = 31;
const int MAX_MONTH = 12;
const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;


// https://howardhinnant.github.io/date_algorithms.html#is_leap
std::tuple<unsigned, Month, int> GetDateFromTimestamp(unsigned timestamp)
{
	timestamp += SHIFT;
	unsigned era = timestamp / ERA_DAYS;
	unsigned dayOfEra = timestamp - era * ERA_DAYS;
	unsigned yearOfEra = (dayOfEra - dayOfEra / (YEAR * 4) + dayOfEra / 36524 - dayOfEra / MAX_ERA_DAY) / YEAR;
	unsigned y = yearOfEra + era * ERA_PERIOD;
	unsigned dayOfYear = dayOfEra - (YEAR * yearOfEra + yearOfEra / 4 - yearOfEra / CENTURY);
	unsigned primeMonth = (5 * dayOfYear + 2) / 153;

	auto day = dayOfYear - (153 * primeMonth + 2) / 5 + 1;

	auto intMonth = primeMonth < 10
		? primeMonth + 3
		: primeMonth - 9;

	auto month = static_cast<Month>(intMonth);
	auto year = y + (intMonth <= 2);

	return std::tuple{day, month, year};
}

bool IsLeap(unsigned year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

void AssertYearIsValid(unsigned year)
{
	if (MIN_YEAR > year || year > MAX_YEAR)
	{
		throw std::runtime_error("Invalid year");
	}
}

void AssertMonth(unsigned month)
{
	if (month > MAX_MONTH)
	{
		throw std::runtime_error("Invalid month");
	}
}

void AssertDayIsValid(unsigned day, Month month, unsigned year)
{
	const int maxFebruaryDay = 28;

	if (MIN_DAY > day)
	{
		throw std::runtime_error("Invalid day");
	}

	if (month == Month::FEBRUARY)
	{
		if (IsLeap(year) && day > maxFebruaryDay + 1 ||
			!IsLeap(year) && day > maxFebruaryDay)
		{
			throw std::runtime_error("Invalid day");
		}
	}
	else
	{
		if (day > MAX_DAY)
		{
			throw std::runtime_error("Invalid day");
		}
	}
}

Date::Date()
	: m_timestamp(0)
{
}

Date::Date(unsigned int timestamp)
	: m_timestamp(timestamp)
{
	AssertTimestampIsValid();
}

Date::Date(unsigned int day, Month month, unsigned int year)
{
	AssertYearIsValid(year);
	AssertDayIsValid(day, month, year);

	auto intMonth = static_cast<int>(month);

	// https://howardhinnant.github.io/date_algorithms.html#is_leap
	year -= intMonth <= 2;
	unsigned era = year / ERA_PERIOD;
	unsigned yearOfEra = year - era * ERA_PERIOD;
	unsigned dayOfYear = (153 * (intMonth > 2 ? intMonth - 3 : intMonth + 9) + 2) / 5 + day - 1;
	unsigned dayOfEra = yearOfEra * YEAR + yearOfEra / 4 - yearOfEra / CENTURY + dayOfYear;

	m_timestamp = era * ERA_DAYS + dayOfEra - SHIFT;
}

unsigned Date::GetDay() const
{
	auto [day, _, __] = GetDateFromTimestamp(m_timestamp);
	return day;
}

Month Date::GetMonth() const
{
	auto [_, month, __] = GetDateFromTimestamp(m_timestamp);
	return month;
}

unsigned Date::GetYear() const
{
	auto [_, __, year] = GetDateFromTimestamp(m_timestamp);
	return year;
}

WeekDay Date::GetWeekDay() const
{
	unsigned dayOfWeek = (m_timestamp + 4) % 7;
	return static_cast<WeekDay>(dayOfWeek);
}

Date& Date::operator++()
{
	m_timestamp++;
	AssertTimestampIsValid();
	return *this;
}

Date Date::operator++(int)
{
	Date copyDate(m_timestamp);
	++(*this);
	AssertTimestampIsValid();
	return copyDate;
}

Date& Date::operator--()
{
	m_timestamp--;
	AssertTimestampIsValid();
	return *this;
}

Date Date::operator--(int)
{
	Date copyDate(m_timestamp);
	--(*this);
	AssertTimestampIsValid();
	return copyDate;
}

Date Date::operator+(unsigned int days) const
{
	return Date(m_timestamp + days);
}

Date operator+(unsigned days, const Date& date)
{
	return Date(date.m_timestamp + days);
}

Date Date::operator-(unsigned int days) const
{
	return Date(m_timestamp - days);
}

unsigned Date::operator-(const Date& date) const
{
	return m_timestamp - date.m_timestamp;
}

Date& Date::operator+=(unsigned int days)
{
	m_timestamp += days;
	AssertTimestampIsValid();
	return *this;
}

Date& Date::operator-=(unsigned int days)
{
	m_timestamp -= days;
	AssertTimestampIsValid();
	return *this;
}

std::ostream& operator<<(std::ostream& output, const Date& date)
{
	auto day = date.GetDay();
	auto month = date.GetMonth();
	if (day < 10)
	{
		output << '0';
	}
	output << day << '.';
	if (month < Month::OCTOBER)
	{
		output << '0';
	}
	output << static_cast<int>(date.GetMonth()) << '.'
		   << date.GetYear();
	return output;
}

std::istream& operator>>(std::istream& input, Date& date)
{
	const char delimiter = '.';

	std::string dayString;
	std::string monthString;
	std::string yearString;
	if (!std::getline(input, dayString, delimiter) ||
		!std::getline(input, monthString, delimiter) ||
		!std::getline(input, yearString))
	{
		input.setstate(std::ios_base::failbit);
		return input;
	}

	auto day = std::stoi(dayString);
	auto intMonth = std::stoi(monthString);
	AssertMonth(intMonth);
	auto month = static_cast<Month>(intMonth);
	auto year = std::stoi(yearString);

	Date newDate(day, month, year);
	date = newDate;
	return input;
}

void Date::AssertTimestampIsValid() const
{
	if (m_timestamp > MAX_TIMESTAMP)
	{
		throw std::runtime_error("Invalid timestamp");
	}
}
