#pragma once

#include <string>
#include <unordered_map>
#include <set>

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

// TODO: move
// TODO: разделить на 2
std::string GetFileName(int argc, char* argv[]);
Dictionary ReadDict(const std::string& dictFileName);
void StartDictionary(Dictionary& dict, const std::string& dictFileName);
