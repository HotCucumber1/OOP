#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <string>
#include <limits>
#include <cmath>


struct InputParams
{
	int destinationRadix;
    int value;
};

InputParams ParseArgs(int argc, char* argv[]);
std::string IntToString(int n, int radix);
int GetRadix(const std::string& radixStr);
int StringToInt(const std::string& str, int radix);
char IntToChar(int number);
int CharToInt(char ch, int radix);
bool IsOverflow(int value, int addition);
void AssertArgCount(int argc);
void AssertRadix(int radix);

int main(int argc, char* argv[])
{
	try
	{
		InputParams inputParams = ParseArgs(argc, argv);
		std::string resultNumber = IntToString(inputParams.value,
												inputParams.destinationRadix);
		std::cout << resultNumber << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}

InputParams ParseArgs(int argc, char* argv[])
{
    AssertArgCount(argc);

	int sourceRadix = GetRadix(argv[1]);
	int destinationRadix = GetRadix(argv[2]);
	int value = StringToInt(argv[3], sourceRadix);

	return {
		destinationRadix,
		value
	};
}

int GetRadix(const std::string& radixStr)
{
	const int inputRadix = 10;

	int radix = StringToInt(radixStr, inputRadix);
	AssertRadix(radix);

	return radix;
}

int StringToInt(const std::string& str, int radix)
{
	int value = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		char digit = str[str.length() - i - 1];
		if (digit == '-')
		{
			value *= (-1);
			continue;
		}
		int addition = CharToInt(digit, radix) * std::pow(radix, i);
		if (IsOverflow(value, addition))
		{
			throw std::invalid_argument("Overflow");
		}
		value += addition;
	}
    return value;
}

std::string IntToString(int n, int radix)
{
	std::string value;
	int positiveNumber = std::abs(n);
    while (positiveNumber >= radix)
	{
		int remainder = positiveNumber % radix;
		value += IntToChar(remainder);
		positiveNumber /= radix;
	}
	value += IntToChar(positiveNumber);
	value += (n < 0) ? "-" : "";
	std::reverse(value.begin(), value.end());
	return value;
}

char IntToChar(int number)
{
	const int decimal = 10;
	return number < decimal
		? ('0' + number)
		: ('A' + (number - decimal));
}

int CharToInt(char ch, int radix)
{
	const int decimal = 10;
	bool isDigit = ch >= '0' and ch <= '9';
	bool isLetter = ch >= 'A' and ch <= 'Z';

	if (!isDigit && !isLetter)
	{
		throw std::runtime_error("Invalid digit");
	}
	int number = (isDigit)
		? ch - '0'
		: ch - 'A' + decimal;
	if (number >= radix)
	{
		throw std::runtime_error("Invalid radix");
	}
	return number;
}

void AssertArgCount(int argc)
{
    const int argcNumber = 4;
    if (argc != argcNumber)
    {
		throw std::invalid_argument("Wrong argument number");
    }
}

void AssertRadix(int radix)
{
	const int minRadix = 2;
	const int maxRadix = 36;

	if (radix < minRadix || radix > maxRadix)
	{
		throw std::invalid_argument("Wrong notation radix");
	}
}

bool IsOverflow(int value, int addition)
{
	return value > std::numeric_limits<int>::max() - addition;
}
