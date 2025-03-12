#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <set>

enum class State
{
	Searching,
	End,
	Adding,
	Saving,
};

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

void AssertValuesNumber(const std::vector<std::string>& values);
void AddToDict(Dictionary& dict, const std::string& key, const std::set<std::string>& values);
std::string Trim(const std::string& str, char trimmedCh = ' ');
std::vector<std::string> Split(const std::string& str, char delimiter = ' ');
std::pair<std::string, std::string> GetDictValues(const std::string& str, char delimiter);
void PrintSet(const std::set<std::string>& set, std::ostream& output);
void PrintDict(const Dictionary& dict, std::ostream& output);
std::string ToLower(const std::string& str);
void AssertFileIsOpen(const std::istream& file);
void SaveDictToFile(Dictionary& dict, const std::string& fileName);
void AddWordToDict(Dictionary& dict, const std::string& key, const std::string& word);
bool NeedToSave(const std::string& status);
bool IsValueFound(Dictionary& dict, const std::string& key);
std::set<std::string> GetValue(Dictionary& dict, const std::string& key);
State HandleSearchingState(Dictionary& dict, std::string& searchedStr,
						   std::string& newValue, bool& isChanged);
State HandleAddingState(Dictionary& dict, const std::string& searchedStr,
						const std::string& newValue, bool& isChanged);
State HandleSavingState(Dictionary& dict, const std::string& dictFileName);
