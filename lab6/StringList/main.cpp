#include "Model/StringList.h"
#include <iostream>


int main()
{
	try
	{
		StringList original;
		original.PushBack("Hello");
		original.PushBack("World");

		StringList copy(original);

		auto second = ++copy.begin();
		std::cout << second->data << std::endl;

		original.PushBack("Testing");
		std::cout << original.begin()->data << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
}