#include "masks.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

enum class ActionType
{
	Crypt,
	Decrypt
};

struct InputParams
{
	ActionType action;
	std::shared_ptr<std::istream> inputFile;
	std::shared_ptr<std::ostream> outputFile;
	unsigned char key;
};

InputParams ParseArgs(int argc, char* argv[]);
ActionType GetActionType(const std::string& actionStr);
unsigned char GetKey(const std::string& keyStr);
void Crypt(std::istream& input, std::ostream& output, unsigned char key);
void Decrypt(std::istream& input, std::ostream& output, unsigned char key);
char GetCryptedChar(char ch, unsigned char key);
char GetDecryptedChar(char ch, unsigned char key);
void AssertIsDecimal(const std::string& numberStr);
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
			Crypt(*inputParams.inputFile, *inputParams.outputFile, inputParams.key);
			break;
		case ActionType::Decrypt:
			Decrypt(*inputParams.inputFile, *inputParams.outputFile, inputParams.key);
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

	auto inputFile= std::make_shared<std::ifstream>(argv[2], std::ios::binary);
	AssertFileIsOpen(*inputFile);
	auto outputFile= std::make_shared<std::ofstream>(argv[3], std::ios::binary);

	unsigned char key = GetKey(argv[4]);
	return {
		action,
		inputFile,
		outputFile,
		key
	};
}

void Crypt(std::istream& input, std::ostream& output, unsigned char key)
{
	char byte;
	while (input.get(byte))
	{
		output << GetCryptedChar(byte, key);
	}
}

void Decrypt(std::istream& input, std::ostream& output, unsigned char key)
{
	char byte;
	while (input.get(byte))
	{
		output << GetDecryptedChar(byte, key);
	}
}

char GetCryptedChar(char ch, unsigned char key)
{
	char outChar = 0;
	char cryptedByte = ch ^ key;

	outChar |= (cryptedByte & eighthByte) >> 2;
	outChar |= (cryptedByte & seventhByte) >> 5;
	outChar |= (cryptedByte & sixthByte) >> 5;
	outChar |= (cryptedByte & fifthByte) << 3;
	outChar |= (cryptedByte & fourthByte) << 3;
	outChar |= (cryptedByte & thirdByte) << 2;
	outChar |= (cryptedByte & secondByte) << 2;
	outChar |= (cryptedByte & firstByte) << 2;

	return outChar;
}

char GetDecryptedChar(char ch, unsigned char key)
{
	char decryptedChar = 0;
	decryptedChar |= (ch & eighthByte) >> 3;
	decryptedChar |= (ch & seventhByte) >> 3;
	decryptedChar |= (ch & sixthByte) << 2;
	decryptedChar |= (ch & fifthByte) >> 2;
	decryptedChar |= (ch & fourthByte) >> 2;
	decryptedChar |= (ch & thirdByte) >> 2;
	decryptedChar |= (ch & secondByte) << 5;
	decryptedChar |= (ch & firstByte) << 5;

	return decryptedChar ^ key;
}

ActionType GetActionType(const std::string& actionStr)
{
	const std::string crypt = "crypt";
	const std::string decrypt = "decrypt";

	if (actionStr == crypt)
	{
		return ActionType::Crypt;
	}
	if (actionStr == decrypt)
	{
		return ActionType::Decrypt;
	}
	throw std::invalid_argument("Wrong action argument");
}

unsigned char GetKey(const std::string& keyStr)
{
	AssertIsDecimal(keyStr);
	int keyNumber = std::stoi(keyStr);

	if (keyNumber < std::numeric_limits<unsigned char>::min() or
		keyNumber > std::numeric_limits<unsigned char>::max())
	{
		throw std::invalid_argument("Wrong key argument");
	}
	return static_cast<unsigned char>(keyNumber);
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

void AssertIsDecimal(const std::string& numberStr)
{
	for (const auto& ch : numberStr)
	{
		if (!std::isdigit(ch))
		{
			throw std::invalid_argument("Wrong key argument");
		}
	}
}