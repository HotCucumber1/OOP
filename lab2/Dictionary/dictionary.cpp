#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <ranges>

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

Dictionary ReadDict(const std::string& dictFileName);
std::pair<std::string, std::string> GetDictValues(const std::string& str, char delimiter);
std::vector<std::string> Split(const std::string& str, char delimiter);
std::string Trim(const std::string& str, char trimmedCh);
std::string ToLower(const std::string& str);
std::string GetFileName(int argc, char* argv[]);
void StartDictionary(Dictionary& dict, const std::string& dictFileName);
void PrintDict(const Dictionary& dict, std::ostream& output);
void PrintSet(const std::set<std::string>& set, std::ostream& output);
void AddToDict(Dictionary& dict, std::string key, std::set<std::string> values);
void AssertValuesNumber(const std::vector<std::string>& values);
void AssertArgumentNumber(int argc);
void AssertFileIsOpen(const std::istream& file);

int main(int argc, char* argv[])
{
	try
	{
		std::string dictFileName = GetFileName(argc, argv);
		Dictionary dict = ReadDict(dictFileName);
		StartDictionary(dict, dictFileName);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
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
	for (const auto& item : dict)
	{
		if (ToLower(key) == ToLower(item.first))
		{
			return true;
		}
	}
	return false;
}

std::set<std::string> GetValue(Dictionary& dict, const std::string& key)
{
	if (dict.find(key) == dict.end())
	{
		return dict[ToLower(key)];
	}
	return dict[key];
}

void StartDictionary(Dictionary& dict, const std::string& dictFileName)
{
	enum class State
	{
		Searching,
		End,
		Adding,
		Saving,
	};
	bool isChanged = false;

	State state = State::Searching;
	std::string searchedStr;
	std::string newValue;
	while (state != State::End)
	{
		switch (state)
		{
		case State::Saving:
		{
			std::getline(std::cin, searchedStr);
			if (NeedToSave(searchedStr))
			{
				SaveDictToFile(dict, dictFileName);
			}
			state = State::End;
			break;
		}
		case State::Adding:
		{
			AddWordToDict(dict, searchedStr, newValue);
			isChanged = true;
			state = State::Searching;
			break;
		}
		case State::Searching:
		{
			std::getline(std::cin, searchedStr);
			if (searchedStr == "...")
			{
				if (!isChanged)
				{
					state = State::End;
					break;
				}
				std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;
				state = State::Saving;
				break;
			}
			if (IsValueFound(dict, searchedStr))
			{
				auto values = GetValue(dict, searchedStr);
				PrintSet(values, std::cout);
				break;
			}

			std::cout << "Неизвестное слово \"" << searchedStr << "\". Введите перевод или пустую строку для отказа." << std::endl;
			std::getline(std::cin, newValue);;
			if (newValue == "")
			{
				std::cout << "Слово \"" << searchedStr << "\" проигнорировано." << std::endl;
				break;
			}
			state = State::Adding;
			break;
		}
		case State::End:
			break;
		}
	}
}


void AddToDict(Dictionary& dict, std::string key, std::set<std::string> values)
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

std::pair<std::string, std::string> GetDictValues(const std::string& str, char delimiter)
{
	std::vector<std::string> values = Split(str, delimiter);
	AssertValuesNumber(values);
	return std::make_pair(values[0], values[1]);
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

void PrintDict(const Dictionary& dict, std::ostream& output)
{
	for (const auto& [key, value] : dict)
	{
		output << key << " : ";
		PrintSet(value, output);
	}
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

std::string ToLower(const std::string& str)
{
	std::string lowerStr;
	for (auto& ch : str)
	{
		lowerStr += std::tolower(ch, std::locale("ru_RU.UTF-8"));
	}
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

void AssertValuesNumber(const std::vector<std::string>& values)
{
	const int valuesNumber = 2;
	if (values.size() < valuesNumber)
	{
		throw std::runtime_error("Wrong dictionary file type");
	}
}