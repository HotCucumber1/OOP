#include "Dictionary.hpp"
#include <iostream>

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