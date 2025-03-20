#include "Dictionary.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>


void AssertValuesNumber(const std::vector<std::string>& values)
{
	const int valuesNumber = 2;
	if (values.size() < valuesNumber)
	{
		throw std::runtime_error("Wrong dictionary file type");
	}
}

void AssertFileIsOpen(const std::istream& file)
{
	if (file.fail())
	{
		throw std::invalid_argument("Failed to open file");
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

std::string ToLower(const std::string& str)
{
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),[](unsigned char ch) {
		return tolower(ch);
	});
	return lowerStr;
}

std::set<std::string> GetTranslation(Dictionary& dict, const std::string& key)
{
	if (dict.find(key) == dict.end())
	{
		return dict[ToLower(key)];
	}
	return dict[key];
}


std::pair<std::string, std::string> GetDictValues(const std::string& str, char delimiter)
{
	std::vector<std::string> values = Split(str, delimiter);
	AssertValuesNumber(values);
	return std::make_pair(values[0], values[1]);
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

bool IsTranslationFound(Dictionary& dict, const std::string& key)
{
	return std::ranges::any_of(dict, [&key](const auto& item) {
		return ToLower(item.first) == ToLower(key);
	});
}
