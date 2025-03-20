#include "Dictionary.h"
#include <algorithm>
#include <iostream>
#include <fstream>


enum class State
{
	Searching,
	End,
	Adding,
	Saving,
};


std::string GetFileName(int argc, char* argv[]);
void AssertArgumentNumber(int argc);
bool NeedToSave(const std::string& status);
std::pair<std::string, std::string> GetDictValues(const std::string& str, char delimiter);
State HandleSearchingState(Dictionary& dict, std::string& searchedStr,
						   std::string& newValue, bool& isChanged);
State HandleAddingState(Dictionary& dict, const std::string& searchedStr,
						const std::string& newValue, bool& isChanged);
State HandleSavingState(Dictionary& dict, const std::string& dictFileName);
void StartDictionaryApp(Dictionary& dict, const std::string& dictFileName);


int main(int argc, char* argv[])
{
	try
	{
		std::string dictFileName = GetFileName(argc, argv);
		Dictionary dict = ReadDict(dictFileName);
		StartDictionaryApp(dict, dictFileName);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}


void StartDictionaryApp(Dictionary& dict, const std::string& dictFileName)
{
	State state = State::Searching;
	std::string searchedStr;
	std::string newValue;
	bool isChanged = false;

	while (state != State::End)
	{
		switch (state)
		{
		case State::Searching:
			state = HandleSearchingState(dict, searchedStr, newValue, isChanged);
			break;
		case State::Adding:
			state = HandleAddingState(dict, searchedStr, newValue, isChanged);
			break;
		case State::Saving:
			state = HandleSavingState(dict, dictFileName);
			break;
		default:
			break;
		}
	}
}


std::string GetFileName(int argc, char* argv[])
{
	AssertArgumentNumber(argc);
	return argv[1];
}

void AssertArgumentNumber(int argc)
{
	const int argumentsNumber = 2;
	if (argc != argumentsNumber)
	{
		throw std::invalid_argument("Wrong argument number");
	}
}

std::string ToLower(const std::string& str)
{
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),[](unsigned char ch) {
		return tolower(ch);
	});
	return lowerStr;
}


bool NeedToSave(const std::string& status)
{
	const std::string needToSave = "y";
	return ToLower(status) == needToSave;
}


void PrintSet(const std::set<std::string>& set, std::ostream& output)
{
	bool first = true;
	for (const auto& elem : set)
	{
		if (!first)
		{
			output << ", ";
		}
		output << elem;
		first = false;
	}
	output << std::endl;
}

void PrintDict(const Dictionary& dict, std::ostream& output)
{
	for (const auto& [key, value] : dict)
	{
		output << key << " : ";
		PrintSet(value, output);
	}
}

State HandleSearchingState(Dictionary& dict, std::string& searchedStr, std::string& newValue, bool& isChanged)
{
	const std::string endStr = "...";
	std::getline(std::cin, searchedStr);

	if (searchedStr == endStr)
	{
		if (!isChanged)
		{
			return State::End;
		}
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
		return State::Saving;
	}
	if (IsTranslationFound(dict, searchedStr))
	{
		auto values = GetTranslation(dict, searchedStr);
		PrintSet(values, std::cout);
		return State::Searching;
	}

	std::cout << "Неизвестное слово \"" << searchedStr << "\". Введите перевод или пустую строку для отказа." << std::endl;
	std::getline(std::cin, newValue);
	if (newValue.empty())
	{
		std::cout << "Слово \"" << searchedStr << "\" проигнорировано." << std::endl;
		return State::Searching;
	}
	return State::Adding;
}

void SaveDictToFile(Dictionary& dict, const std::string& fileName)
{
	std::ofstream output(fileName);
	PrintDict(dict, output);
	std::cout << "Изменения сохранены. До свидания." << std::endl;
}

void AddWordToDict(Dictionary& dict, const std::string& key, const std::string& word)
{
	std::set<std::string> addingValue = {word};
	AddToDict(dict, key, addingValue);
	std::cout << "Слово \"" << key  << "\" сохранено в словаре как \"" << word << "\"." << std::endl;
}

State HandleAddingState(Dictionary& dict, const std::string& searchedStr, const std::string& newValue, bool& isChanged)
{
	AddWordToDict(dict, searchedStr, newValue);
	isChanged = true;
	return State::Searching;
}

State HandleSavingState(Dictionary& dict, const std::string& dictFileName)
{
	std::string input;
	std::getline(std::cin, input);

	if (NeedToSave(input))
	{
		SaveDictToFile(dict, dictFileName);
	}
	return State::End;
}