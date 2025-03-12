#pragma once
#include <set>
#include <fstream>

int GetUpperBoundFromCLI(int argc, char* argv[]);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(const std::set<int>& set, std::ostream& output);
