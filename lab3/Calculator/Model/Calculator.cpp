#include "Calculator.h"
#include "../Exception/Exception.h"


void Calculator::AddVariable(const std::string& identifier, const Variable& variable)
{
	AssertIdentifierUnique(identifier);
	m_variables[identifier] = std::make_shared<Variable>(variable);
}

void Calculator::SetVariable(const std::string& identifier, const Variable& variable)
{
	if (m_variables.find(identifier) == m_variables.end())
	{
		AddVariable(identifier, variable);
	}
	m_variables[identifier]->SetValue(variable);
}

void Calculator::AddFunction(const std::string& identifier, const std::shared_ptr<Function>& function)
{
	AssertIdentifierUnique(identifier);
	m_functions[identifier] = function;
}

double Calculator::GetIdentifierValue(const std::string& identifier) const
{
	auto variableValue = m_variables.find(identifier);
	if (variableValue != m_variables.end())
	{
		return variableValue->second->GetValue();
	}

	auto functionValue = m_functions.find(identifier);
	if (functionValue != m_functions.end())
	{
		return functionValue->second->GetValue();
	}
	throw UndeclaredIdentifierException();
}

std::shared_ptr<Computable> Calculator::GetIdentifier(const std::string& identifier) const
{
	auto variable = m_variables.find(identifier);
	if (variable != m_variables.end())
	{
		return variable->second;
	}

	auto function = m_functions.find(identifier);
	if (function != m_functions.end())
	{
		return function->second;
	}
	throw UndeclaredIdentifierException();
}

std::map<std::string, double> Calculator::GetVariables() const
{
	std::map<std::string, double> values;
	for (const auto& [identifier, variable] : m_variables)
	{
		values[identifier] = variable->GetValue();
	}
	return values;
}

std::map<std::string, double> Calculator::GetFunctions() const
{
	std::map<std::string, double> values;
	for (const auto& [identifier, function] : m_functions)
	{
		values[identifier] = function->GetValue();
	}
	return values;
}

void Calculator::AssertIdentifierUnique(const std::string& identifier) const
{
	bool variableExists = m_variables.find(identifier) != m_variables.end();
	bool functionExists = m_functions.find(identifier) != m_functions.end();

	if (variableExists || functionExists)
	{
		throw IdentifierIsNotUniqueException();
	}
}