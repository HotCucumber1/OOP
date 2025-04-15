#include "CalculatorController.h"
#include "../Exception/Exception.h"
#include <cmath>
#include <iomanip>
#include <regex>


const int DIGITS_AFTER_POINT = 2;
const char IDENTIFIER_VALUE_DELIMITER = '=';


void PrintValues(const std::map<std::string, double>& values, std::ostream& output)
{
	output << std::fixed << std::setprecision(DIGITS_AFTER_POINT);

	for (const auto& [identifier, value] : values)
	{
		output << identifier << ':' << value << std::endl;
	}
}

std::string Trim(const std::string& str, char trimmedCh = ' ')
{
	size_t first = str.find_first_not_of(trimmedCh);
	if (first == std::string::npos)
	{
		return "";
	}
	size_t last = str.find_last_not_of(trimmedCh);

	return str.substr(first, last - first + 1);
}

void AssertIdentifierIsValid(const std::string& identifier)
{
	const std::regex identifierPattern("^[a-zA-Z_][a-zA-Z0-9_]*$");
	if (!std::regex_match(identifier, identifierPattern))
	{
		throw InvalidCommandUsageException();
	}
}

CalculatorController::CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_commandMap({
		  {"var", [this](std::istream& stream) { return InitVariable(stream); }},
		  {"let", [this](std::istream& stream) { return SetVariable(stream); }},
		  {"fn", [this](std::istream& stream) { return SetFunction(stream); }},
		  {"print", [this](std::istream& stream) { return PrintIdentifier(stream); }},
		  {"printvars", [this](std::istream& stream) { return PrintVariables(stream); }},
		  {"printfns", [this](std::istream& stream) { return PrintFunctions(stream); }},
	  })
{
}

void CalculatorController::HandleCommand()
{
	try
	{
		std::string commandLine;
		getline(m_input, commandLine);
		std::istringstream stream(commandLine);

		std::string command;
		stream >> command;

		auto commandIt = m_commandMap.find(command);
		if (commandIt == m_commandMap.end())
		{
			throw UnknownCommandException();
		}
		commandIt->second(stream);
	}
	catch (const std::exception& exception)
	{
		m_output << exception.what() << std::endl;
	}
}

void CalculatorController::InitVariable(std::istream& input)
{
	std::string identifier;
	input >> identifier;
	identifier = Trim(identifier);

	AssertIdentifierIsValid(identifier);
	Variable variable;
	m_calculator.AddVariable(identifier, variable);
}

void CalculatorController::SetVariable(std::istream& input)
{
	std::string identifier;
	std::getline(input, identifier, IDENTIFIER_VALUE_DELIMITER);
	identifier = Trim(identifier);

	AssertIdentifierIsValid(identifier);

	Variable variable;
	try
	{
		double value;
		input >> value;
		variable.SetValue(value);
	}
	catch (const std::invalid_argument& exception)
	{
		std::string valueIdent;
		input >> valueIdent;
		valueIdent = Trim(valueIdent);
		variable.SetValue(m_calculator.GetIdentifierValue(valueIdent));
	}
	m_calculator.SetVariable(identifier, variable);
}

void CalculatorController::SetFunction(std::istream& input)
{
	std::string identifier;
	std::getline(input, identifier, IDENTIFIER_VALUE_DELIMITER);
	identifier = Trim(identifier);

	std::string expression;
	std::getline(input, expression);

	auto func = std::make_shared<Function>();
	size_t operationPos = expression.find_first_of("+-*/");

	if (operationPos == expression.size())
	{
		func->SetValue(m_calculator.GetIdentifier(expression));
		return;
	}

	std::string identifier1 = Trim(expression.substr(0, operationPos));
	std::string operation = expression.substr(operationPos, 1);
	std::string identifier2 = Trim(expression.substr(operationPos + 1));

	// TODO: ???
	func->SetExpression(
		std::move(m_calculator.GetIdentifier(identifier1)),
		std::move(m_calculator.GetIdentifier(identifier2)),
		operation.at(0)
	);
	m_calculator.AddFunction(identifier, func);
}

void CalculatorController::PrintIdentifier(std::istream& input)
{
	std::string identifier;
	input >> identifier;

	double value = m_calculator.GetIdentifierValue(identifier);
	m_output << std::fixed << std::setprecision(DIGITS_AFTER_POINT);
	m_output << value << std::endl;
}

void CalculatorController::PrintVariables(std::istream&)
{
	auto variables = m_calculator.GetVariables();
	PrintValues(variables, m_output);
}

void CalculatorController::PrintFunctions(std::istream&)
{
	auto functionsValues = m_calculator.GetFunctions();
	PrintValues(functionsValues, m_output);
}