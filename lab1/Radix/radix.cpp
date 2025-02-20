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

const std::string validDigits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

InputParams ParseArgs(int argc, char* argv[]);
std::string GetNotation(int value, int radix);
std::string IntToString(int n, int radix);
int GetRadix(const std::string& radixStr);
int StringToInt(const std::string& str, int radix);
bool IsOverflow(int value, int addition);
bool isCharInString(const std::string& str, char ch);
void AssertArgCount(int argc);
void AssertRadix(int radix);

int main(int argc, char* argv[])
{
	try
	{
		InputParams inputParams = ParseArgs(argc, argv);
		std::string requiredNotation = GetNotation(inputParams.value,
												inputParams.destinationRadix);
		std::cout << requiredNotation << std::endl;
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

std::string GetNotation(int value, int radix)
{
	return IntToString(value, radix);
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
	const std::string allowedDigits = validDigits.substr(0, radix);

	int value = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		char digit = str[str.length() - i - 1];
		if (digit == '-')
		{
			value *= (-1);
			continue;
		}
		if (!isCharInString(allowedDigits, digit))
		{
			throw std::invalid_argument("Wrong notation argument");
		}
		int addition = allowedDigits.find(digit) * std::pow(radix, i);
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
	int wholeNumber = std::abs(n);
    while (wholeNumber >= radix)
	{
		int remainder = wholeNumber % radix;
		value += validDigits[remainder];
		wholeNumber /= radix;
	}
	value += validDigits[wholeNumber];
	value += (n < 0) ? "-" : "";
	std::reverse(value.begin(), value.end());
	return value;
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

bool isCharInString(const std::string& str, char ch)
{
	return str.find(ch) != std::string::npos;
}