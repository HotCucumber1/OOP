#include "Function.h"
#include <utility>
#include <unordered_map>
#include <functional>
#include <cmath>


using Operation = std::function<double(const std::shared_ptr<Computable>, const std::shared_ptr<Computable>)>;
const std::unordered_map<char, Operation> OPERATIONS = {
	{'+', [](const std::shared_ptr<Computable>& arg1, const std::shared_ptr<Computable>& arg2) { return arg1->GetValue() + arg2->GetValue(); }},
	{'-', [](const std::shared_ptr<Computable>& arg1, const std::shared_ptr<Computable>& arg2) { return arg1->GetValue() - arg2->GetValue(); }},
	{'*', [](const std::shared_ptr<Computable>& arg1, const std::shared_ptr<Computable>& arg2) { return arg1->GetValue() * arg2->GetValue(); }},
	{'/', [](const std::shared_ptr<Computable>& arg1, const std::shared_ptr<Computable>& arg2) { return arg1->GetValue() / arg2->GetValue(); }}
};

void Function::SetValue(std::shared_ptr<Computable> value)
{
	m_value = std::move(value);
	m_arg1 = nullptr;
	m_arg2 = nullptr;
}

void Function::SetExpression(
	std::shared_ptr<Computable> arg1,
	std::shared_ptr<Computable> arg2,
	char operation)
{
	m_arg1 = std::move(arg1);
	m_arg2 = std::move(arg2);
	m_operation = operation;

	m_value = nullptr;
}

double Function::GetValue() const
{
	if (m_value == nullptr)
	{
		auto function = OPERATIONS.find(m_operation);
		if (function == OPERATIONS.end())
		{
			return std::nan("");
		}
		return function->second(m_arg1, m_arg2);
	}

	return m_value->GetValue();
}