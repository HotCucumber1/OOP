#include <catch2/catch_all.hpp>
#include "../Model/Calculator.h"
#include "../Exception/Exception.h"

TEST_CASE("Test variable")
{
	SECTION("Test set variable value success")
	{
		double value = 69.69;

		Variable variable;
		variable.SetValue(value);
		REQUIRE(variable.GetValue() == value);
	}

	SECTION("Test set variable by another variable success")
	{
		double value = 69.69;

		Variable variable;
		Variable anotherVariable;

		anotherVariable.SetValue(value);
		variable.SetValue(anotherVariable);

		REQUIRE(variable.GetValue() == value);
	}

	SECTION("Test get unsetted variable value success")
	{
		Variable variable;
		REQUIRE(std::isnan(variable.GetValue()));
	}
}

TEST_CASE("Test function")
{
	SECTION("Test set function by variable success")
	{
		double value = 69.69;

		Variable variable;
		variable.SetValue(value);

		Function function;
		function.SetValue(std::make_shared<Variable>(variable));
		REQUIRE(function.GetValue() == value);
	}

	SECTION("Test set function by another function success")
	{
		double value = 69.69;

		Variable variable;
		variable.SetValue(value);
		Function function;
		Function anotherFunction;

		anotherFunction.SetValue(std::make_shared<Variable>(variable));
		function.SetValue(std::make_shared<Function>(anotherFunction));
		REQUIRE(function.GetValue() == value);
	}

	SECTION("Test set function by another function success")
	{
		double value = 69.69;

		Variable variable;
		variable.SetValue(value);
		Function function;
		Function anotherFunction;

		anotherFunction.SetValue(std::make_shared<Variable>(variable));
		function.SetValue(std::make_shared<Function>(anotherFunction));
		REQUIRE(function.GetValue() == value);
	}

	SECTION("Test set function by variable expression success")
	{
		double value = 69.69;

		Variable variable1;
		variable1.SetValue(value);
		Variable variable2;
		variable2.SetValue(value);

		Function function;

		function.SetExpression(
			std::make_shared<Variable>(variable1),
			std::make_shared<Variable>(variable2),
			'+'
		);
		REQUIRE(function.GetValue() == value + value);
	}

	SECTION("Test set function by function expression success")
	{
		double value = 69.69;

		Variable variable;
		variable.SetValue(value);

		Function function1;
		function1.SetValue(std::make_shared<Variable>(variable));
		Function function2;
		function2.SetValue(std::make_shared<Variable>(variable));

		Function function;
		function.SetExpression(
			std::make_shared<Function>(function1),
			std::make_shared<Function>(function2),
			'+'
		);
		REQUIRE(function.GetValue() == value + value);
	}

	SECTION("Test get unsetted function value success")
	{
		Function function;
		REQUIRE(std::isnan(function.GetValue()));
	}

	SECTION("Test division by zero is nan success")
	{
		double value = 0;

		Function function;

		Variable variable1;
		variable1.SetValue(value);
		Variable variable2;
		variable2.SetValue(value);

		function.SetExpression(
			std::make_shared<Variable>(variable1),
			std::make_shared<Variable>(variable2),
			'/'
		);
		REQUIRE(std::isnan(function.GetValue()));
	}

	SECTION("Test function argument is nan success")
	{
		double value = 0;

		Function function;

		Variable variable1;
		variable1.SetValue(value);
		Variable variable2;

		function.SetExpression(
			std::make_shared<Variable>(variable1),
			std::make_shared<Variable>(variable2),
			'+'
		);
		REQUIRE(std::isnan(function.GetValue()));
	}
}

TEST_CASE("Test calculator")
{
	SECTION("Test variable definition success")
	{
		Calculator calculator;

		Variable var;
		calculator.AddVariable("a", var);
		auto ident = calculator.GetIdentifier("a");
		REQUIRE(std::isnan(ident->GetValue()));
	}

	SECTION("Test variable definition with existed identifier fail")
	{
		Calculator calculator;

		Variable var;
		calculator.AddVariable("a", var);
		REQUIRE_THROWS_AS(calculator.AddVariable("a", var), IdentifierIsNotUniqueException);
	}

	SECTION("Test set existed variable success")
	{
		double value = 5;

		Calculator calculator;
		Variable var;
		calculator.AddVariable("a", var);
		Variable var1;
		var1.SetValue(value);
		calculator.SetVariable("a", var1);

		REQUIRE(calculator.GetIdentifier("a")->GetValue() == value);
	}

	SECTION("Test set non existed variable success")
	{
		double value = 5;

		Calculator calculator;
		Variable var;
		var.SetValue(value);
		calculator.SetVariable("a", var);

		REQUIRE(calculator.GetIdentifier("a")->GetValue() == value);
	}

	SECTION("Test set function by variable success")
	{
		double value = 5;

		Calculator calculator;
		Variable var;
		var.SetValue(value);
		Variable var1;
		var1.SetValue(value);
		Function function;
		function.SetExpression(std::make_shared<Variable>(var), std::make_shared<Variable>(var1), '+');

		calculator.AddFunction("b", std::make_shared<Function>(function));
		REQUIRE(calculator.GetIdentifier("b")->GetValue() == value + value);
	}

	SECTION("Test set function by existed identifier fail")
	{
		double value = 10;

		Calculator calculator;
		Variable var;
		calculator.AddVariable("a", var);

		Variable var2;
		var2.SetValue(value);
		Variable var1;
		var1.SetValue(value);
		Function function;
		function.SetExpression(std::make_shared<Variable>(var2), std::make_shared<Variable>(var1), '+');

		REQUIRE_THROWS_AS(calculator.AddFunction("a", std::make_shared<Function>(function)), IdentifierIsNotUniqueException);
	}

	SECTION("Test get existed variable identifier success")
	{
		double value = 5;

		Calculator calculator;
		Variable var;
		var.SetValue(value);
		calculator.SetVariable("a", var);
		REQUIRE(calculator.GetIdentifier("a")->GetValue() == value);
	}

	SECTION("Test get existed function success")
	{
		double value = 5;

		Calculator calculator;
		Variable var;
		var.SetValue(value);
		Variable var1;
		var1.SetValue(value);
		Function function;
		function.SetExpression(std::make_shared<Variable>(var), std::make_shared<Variable>(var1), '+');

		calculator.AddFunction("b", std::make_shared<Function>(function));
		REQUIRE(calculator.GetIdentifier("b")->GetValue() == value + value);
	}

	SECTION("Test get non existed identifier success")
	{
		double value = 5;

		Calculator calculator;
		Variable var;
		var.SetValue(value);
		calculator.SetVariable("a", var);
		REQUIRE_THROWS_AS(calculator.GetIdentifier("xyz")->GetValue(), UndeclaredIdentifierException);
	}

	SECTION("Test get existed variables success")
	{
		std::stringstream input("let a=5\n"
								"let b =69\n");
		std::stringstream output;

		Calculator calculator;
		Variable var1;
		var1.SetValue(5);
		calculator.SetVariable("a", var1);

		Variable var2;
		var2.SetValue(69);
		calculator.SetVariable("b", var2);

		auto variables = calculator.GetVariables();
		REQUIRE(variables["a"] == 5);
		REQUIRE(variables["b"] == 69);
	}

	SECTION("Test get empty variables success")
	{
		Calculator calculator;
		auto variables = calculator.GetVariables();
		REQUIRE(variables.empty());
	}

	SECTION("Test function update after variable update success")
	{
		double value = 74;
		double newValue = 5;

		Calculator calculator;
		Variable var1;
		var1.SetValue(5);
		calculator.SetVariable("a", var1);

		Variable var2;
		var2.SetValue(69);
		calculator.SetVariable("b", var2);

		Function function;
		auto firstVar = calculator.GetIdentifier("a");
		auto secondVar = calculator.GetIdentifier("b");
		function.SetExpression(firstVar, secondVar, '+');
		calculator.AddFunction("x", std::make_shared<Function>(function));
		REQUIRE(calculator.GetIdentifier("x")->GetValue() == value);

		Variable var3;
		var3.SetValue(0);
		calculator.SetVariable("b", var3);

		REQUIRE(calculator.GetIdentifier("x")->GetValue() == newValue);
	}
}
