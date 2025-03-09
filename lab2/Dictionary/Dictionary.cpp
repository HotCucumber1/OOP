#include "Dictionary.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>

enum class State
{
	Searching,
	End,
	Adding,
	Saving,
};

void AssertValuesNumber(const std::vector<std::string>& values)
{
	const int valuesNumber = 2;
	if (values.size() < valuesNumber)
	{
		throw std::runtime_error("Wrong dictionary file type");
	}
}

void AddToDict(Dictionary& dict, const std::string& key, const std::set<std::string>& values)
{
	if (dict.find(key) != dict.end())
	{
		dict[key].insert(values.begin(), values.end());
	}
	else
	{
		dict[key] = values;
	}
	for (const auto& value : values)
	{
		std::set<std::string> newValue = {key};
		dict[value] = newValue;
	}
}

std::string Trim(const std::string& str, char trimmedCh)
{
	size_t first = str.find_first_not_of(trimmedCh);
	if (first == std::string::npos)
	{
		return "";
	}
	size_t last = str.find_last_not_of(trimmedCh);
	return str.substr(first, last - first + 1);
}

std::vector<std::string> Split(const std::string& str, char delimiter)
{
	std::vector<std::string> items;
	std::string item;

	std::istringstream itemStream(str);
	while (std::getline(itemStream, item, delimiter))
	{
		items.push_back(Trim(item, ' '));
	}
	return items;
}

std::pair<std::string, std::string> GetDictValues(const std::string& str, char delimiter)
{
	std::vector<std::string> values = Split(str, delimiter);
	AssertValuesNumber(values);
	return std::make_pair(values[0], values[1]);
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

std::string ToLower(const std::string& str)
{
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),[](unsigned char ch) {
		return tolower(ch);
	});
	return lowerStr;
}

void AssertArgumentNumber(int argc)
{
	const int argumentsNumber = 2;
	if (argc != argumentsNumber)
	{
		throw std::invalid_argument("Wrong argument number");
	}
}

void AssertFileIsOpen(const std::istream& file)
{
	if (file.fail())
	{
		throw std::invalid_argument("Failed to open file");
	}
}

std::string GetFileName(int argc, char* argv[])
{
	AssertArgumentNumber(argc);
	return argv[1];
}

Dictionary ReadDict(const std::string& dictFileName)
{
	std::ifstream dictFile(dictFileName);
	AssertFileIsOpen(dictFile);

	Dictionary dict;
	std::string line;
	while (std::getline(dictFile, line))
	{
		std::pair<std::string, std::string> dictArguments = GetDictValues(line, ':');
		std::vector<std::string> values = Split(dictArguments.second, ',');
		std::set<std::string> uniqueValues(values.begin(), values.end());

		AddToDict(dict, dictArguments.first, uniqueValues);
	}
	return dict;
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

bool NeedToSave(const std::string& status)
{
	const std::string needToSave = "y";
	return ToLower(status) == needToSave;
}

bool IsValueFound(Dictionary& dict, const std::string& key)
{
	// TODO: std::range
	return std::any_of(dict.begin(), dict.end(),[&key](const auto& item) {
		return ToLower(item.first) == ToLower(key);
	});
}

std::set<std::string> GetValue(Dictionary& dict, const std::string& key)
{
	if (dict.find(key) == dict.end())
	{
		return dict[ToLower(key)];
	}
	return dict[key];
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
	if (IsValueFound(dict, searchedStr))
	{
		auto values = GetValue(dict, searchedStr);
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

void StartDictionary(Dictionary& dict, const std::string& dictFileName)
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