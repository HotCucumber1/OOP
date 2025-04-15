#pragma once
#include "Variable.h"
#include "Function.h"
#include <string>
#include <map>

class Calculator
{
public:
	void AddVariable(const std::string& identifier, const Variable& variable);
	void SetVariable(const std::string& identifier, const Variable& variable);
	void AddFunction(const std::string& identifier, const std::shared_ptr<Function>& function);

	double GetIdentifierValue(const std::string& identifier) const;
	std::shared_ptr<Computable> GetIdentifier(const std::string& identifier) const;
	std::map<std::string, double> GetVariables() const;
	std::map<std::string, double> GetFunctions() const;
private:
	void AssertIdentifierUnique(const std::string& identifier) const;
private:
	std::map<std::string, std::shared_ptr<Variable>> m_variables = {};
	std::map<std::string, std::shared_ptr<Function>> m_functions = {};
};
