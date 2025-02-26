#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cmath>


enum class ActionType
{
	Crypt,
	Decrypt
};

struct InputParams
{
	ActionType action;
	std::ifstream& inputFile;
	std::ofstream& outputFile;
	unsigned char key;
};

InputParams ParseArgs(int argc, char* argv[]);
ActionType GetActionType(std::string actionStr);
unsigned char GetKey(std::string keyStr);
void Crypt(std::ifstream& input, std::ofstream& output, unsigned char key);
void Decrypt(std::ifstream& input, std::ofstream& output, unsigned char key);
int StringToInt(const std::string& str, int radix);
int CharToInt(char ch, int radix);
bool IsOverflow(int value, int addition);

void AssertArgumentNumber(int argc);
void AssertFileIsOpen(const std::istream& file);

int main(int argc, char* argv[])
{
	try
	{
		InputParams inputParams = ParseArgs(argc, argv);
		switch (inputParams.action)
		{
		case ActionType::Crypt:
			Crypt(inputParams.inputFile, inputParams.outputFile, inputParams.key);
			break;
		case ActionType::Decrypt:
			Decrypt(inputParams.inputFile, inputParams.outputFile, inputParams.key);
			break;
		}
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
	AssertArgumentNumber(argc);
	ActionType action = GetActionType(argv[1]);

	std::ifstream inputFile(argv[2]);
	AssertFileIsOpen(inputFile);
	std::ofstream outputFile(argv[3]);

	unsigned char key = GetKey(argv[4]);
	return {
		action,
		inputFile,
		outputFile,
		key
	};
}

void Crypt(std::ifstream& input, std::ofstream& output, unsigned char key)
{
	char byte;
	while (input.get(byte))
	{
		char outByte = 0;
		char cryptedByte = byte ^ key;

		outByte |= (cryptedByte & 0b10000000) >> 2;
		outByte |= (cryptedByte & 0b01000000) >> 5;
		outByte |= (cryptedByte & 0b00100000) >> 5;
		outByte |= (cryptedByte & 0b00010000) << 3;
		outByte |= (cryptedByte & 0b00001000) << 3;
		outByte |= (cryptedByte & 0b00000100) << 2;
		outByte |= (cryptedByte & 0b00000010) << 2;
		outByte |= (cryptedByte & 0b00000001) << 2;

		output << outByte;
	}
}

void Decrypt(std::ifstream& input, std::ofstream& output, unsigned char key)
{
	char byte;
	while (input.get(byte))
	{
		char cryptedByte = 0;
		cryptedByte |= (byte & 0b10000000) >> 3;
		cryptedByte |= (byte & 0b01000000) >> 3;
		cryptedByte |= (byte & 0b00100000) << 2;
		cryptedByte |= (byte & 0b00010000) >> 2;
		cryptedByte |= (byte & 0b00001000) >> 2;
		cryptedByte |= (byte & 0b00000100) >> 2;
		cryptedByte |= (byte & 0b00000010) << 5;
		cryptedByte |= (byte & 0b00000001) << 5;

		char outByte = cryptedByte ^ key;
		output << outByte;
	}
}

ActionType GetActionType(std::string actionStr)
{
	const std::string crypt = "crypt";
	const std::string decrypt = "decrypt";

	if (actionStr == crypt)
	{
		return ActionType::Crypt;
	}
	else if (actionStr == decrypt)
	{
		return ActionType::Decrypt;
	}
	else
	{
		throw std::invalid_argument("Wrong action argument");
	}
}

unsigned char GetKey(std::string keyStr)
{
	const int decimalRadix = 10;
	int keyNumber = StringToInt(keyStr, decimalRadix);

	if (keyNumber < std::numeric_limits<unsigned char>::min() or
		keyNumber > std::numeric_limits<unsigned char>::max())
	{
		throw std::invalid_argument("Wrong key argument");
	}
	return static_cast<unsigned char>(keyNumber);
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

bool IsOverflow(int value, int addition)
{
	return value > std::numeric_limits<int>::max() - addition;
}

void AssertArgumentNumber(int argc)
{
	const int argumentsNumber = 5;
	if (argc != argumentsNumber)
	{
		throw std::invalid_argument("Wrong argument number");
	}
}

void AssertFileIsOpen(const std::istream& file)
{
	if (file.fail())
	{
		throw std::invalid_argument("Wrong input file");
	}
}