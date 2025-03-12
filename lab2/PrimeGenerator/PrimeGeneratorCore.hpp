#pragma once
#include <vector>

void AssertArgumentNumber(int argc);
void AssertNumberIsPositive(int n);
bool IsNumber(const std::string& stringNumber);
void AssertArgumentIsNumber(const std::string& string);
std::vector<bool> GetSieve(int n);