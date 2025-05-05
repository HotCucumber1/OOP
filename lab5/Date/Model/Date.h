#pragma once
#include <sstream>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

class Date
{
public:
	Date(unsigned day, Month month, unsigned year);
	explicit Date(unsigned timestamp);
	Date();

	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;

	Date& operator++();
	Date& operator--();
	Date operator++(int);
	Date operator--(int);
	Date operator+(unsigned days) const;
	friend Date operator+(unsigned days, const Date& date);
	Date operator-(unsigned days) const;
	unsigned operator-(const Date& date) const;
	Date& operator+=(unsigned days);
	Date& operator-=(unsigned days);
	friend std::ostream& operator<<(std::ostream& output, const Date& date);
	friend std::istream& operator>>(std::istream& input, Date& date);
	friend std::strong_ordering operator<=>(const Date& left, const Date& right) = default;

private:
	void AssertTimestampIsValid() const;

private:
	unsigned m_timestamp;
};
