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
InputParams GetInputParams(char* argv[]);
std::string GetNotation(int value, int radix);
std::string IntToString(int n, int radix, bool& wasError);
int StringToInt(const std::string& str, int radix, bool& wasError);
bool CheckOverflow(int value, int addition);
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
    return GetInputParams(argv);
}

InputParams GetInputParams(char* argv[])
{
	const int inputRadix = 10;
	bool wasError = false;

    int sourceRadix = StringToInt(argv[1], inputRadix, wasError);
	AssertRadix(sourceRadix);

	int destinationRadix = StringToInt(argv[2], inputRadix, wasError);
	AssertRadix(destinationRadix);

	int value = StringToInt(argv[3], sourceRadix, wasError);
    if (wasError)
	{
		throw std::invalid_argument("Wrong notation argument");
	}

    return {
		destinationRadix,
		value
	};
}

std::string GetNotation(int value, int radix)
{
	bool wasError = false;

	std::string outputNotation = IntToString(value, radix, wasError);
	if (wasError)
	{
		throw std::runtime_error("Wrong number");
	}
	return outputNotation;
}


int StringToInt(const std::string& str, int radix, bool& wasError)
{
	const int startPos = 0;
	const std::string allowedDigits = validDigits.substr(startPos, radix);

	int value = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		char digit = str[str.length() - i - 1];
		if (allowedDigits.find(digit) == std::string::npos)
		{
			wasError = true;
		}
		int addition = allowedDigits.find(digit) * std::pow(radix, i);
		if (!CheckOverflow(value, addition))
		{
			wasError = true;
		}
		if (wasError)
		{
			return value;
		}
		value += addition;
	}
    return value;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	const int startPos = 0;
	const std::string allowedDigits = validDigits.substr(startPos, radix);

	std::string value;
	int wholeNumber = n;
    while (wholeNumber >= radix)
	{
		int remainder = wholeNumber % radix;
		value += allowedDigits[remainder];
		wholeNumber /= radix;
	}
	value += allowedDigits[wholeNumber];
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
		throw std::invalid_argument("Wrong notation number");
	}
}

bool CheckOverflow(int value, int addition)
{
	if (value > 0 && addition > 0)
	{
		return value <= std::numeric_limits<int>::max() - addition;
	}
	if (value < 0 && addition < 0)
	{
		return value >= std::numeric_limits<int>::min() + addition;
	}
	return true;
}