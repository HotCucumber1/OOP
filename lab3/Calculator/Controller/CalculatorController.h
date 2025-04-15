#pragma once
#include "../Model/Calculator.h"
#include "sstream"
#include <functional>

class CalculatorController
{
public:
	CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output);
	void HandleCommand();

private:
	void InitVariable(std::istream& input);
	void SetVariable(std::istream& input);
	void SetFunction(std::istream& input);
	void PrintIdentifier(std::istream& input);
	void PrintVariables(std::istream&);
	void PrintFunctions(std::istream&);

private:
	using Handler = std::function<void(std::istream& args)>;
	using CommandMap = std::unordered_map<std::string, Handler>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const CommandMap m_commandMap;
};
