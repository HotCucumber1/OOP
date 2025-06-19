#pragma once
#include <vector>
#include <algorithm>

template<typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	try
	{
		auto it = std::max_element(arr.begin(), arr.end(), less);
		if (it == arr.end())
		{
			return false;
		}
		maxValue = *it;
	}
	catch (const std::exception& exception)
	{
		return false;
	}
	return true;
}