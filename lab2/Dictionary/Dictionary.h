#pragma once

#include <string>
#include <unordered_map>
#include <set>

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

Dictionary ReadDict(const std::string& dictFileName);
void AddToDict(Dictionary& dict, const std::string& key, const std::set<std::string>& values);
std::set<std::string> GetTranslation(Dictionary& dict, const std::string& key);
bool IsTranslationFound(Dictionary& dict, const std::string& key);
