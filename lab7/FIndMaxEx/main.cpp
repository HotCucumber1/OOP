#include "FindMaxEx.h"
#include <string>
#include <iostream>


struct Man
{
	std::string name;
	int height;
	double weight;
};


int main()
{
	std::vector<Man> men = {
		{"Иванов Иван", 185, 82.3},
		{"Петров Петр", 192, 90.1},
		{"Алексеев Алексей", 178, 75.8},
		{"Дмитриев Дмитрий", 190, 95.4},
		{"Александров Александр", 168, 60.2}
	};

	Man tallest;
	Man heaviest;

	auto compareHeight = [](const Man& left, const Man& right) { return left.height < right.height; };
	auto compareWeight = [](const Man& left, const Man& right) { return left.weight < right.weight; };

	if (FindMaxEx(men, tallest, compareHeight))
	{
		std::cout << tallest.name << " - самый высокий!" << std::endl;
	}
	if (FindMaxEx(men, heaviest, compareWeight))
	{
		std::cout << heaviest.name << " - самый тяжелый!" << std::endl;
	}
}