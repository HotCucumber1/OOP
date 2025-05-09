#include "../../StreamValidChecker/StreamValidChecker.h"
#include "Vector.h"
#include <algorithm>
#include <iomanip>

std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> numbers;
	AssertStreamIsValid(input);

	double number;
	while (input >> number)
	{
		numbers.push_back(number);
	}
	AssertStreamIsEnded(input);
	return numbers;
}

std::vector<double> ProcessNumbers(const std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return numbers;
	}
	std::vector<double> processedNumbers = numbers;
	double min = *std::min_element(numbers.begin(), numbers.end());

	std::transform(processedNumbers.begin(), processedNumbers.end(), processedNumbers.begin(),[&min](double number) {
		return number * min;
	});
	return processedNumbers;
}

void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& output)
{
	const int digitsAfterPoint = 3;
	std::vector<double> sortedNumbers = GetSortedNumbers(numbers);

	output << std::fixed << std::setprecision(digitsAfterPoint);
	for (const auto& number : sortedNumbers)
	{
		output << number << ' ';
	}
	output << std::endl;
}

std::vector<double> GetSortedNumbers(const std::vector<double>& numbers)
{
	std::vector<double> sortedNumbers = numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());
	return sortedNumbers;
}
