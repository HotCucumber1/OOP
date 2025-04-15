#include <catch2/catch_all.hpp>
#include "../Controller/CalculatorController.h"
#include "../Exception/Exception.h"
#include "sstream"

TEST_CASE("Test variable definition")
{
	SECTION("Test variable definition success")
	{
		std::stringstream input("var a");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);

		calculatorController.HandleCommand();
		auto ident = calculator.GetIdentifier("a");
		REQUIRE(std::isnan(ident->GetValue()));
	}

	SECTION("Test variable definition with invalid identifier fail")
	{
		std::stringstream input("var 1a");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);

		REQUIRE_THROWS_AS(calculatorController.HandleCommand(), InvalidCommandUsageException);
	}

	SECTION("Test variable definition with existed identifier fail")
	{
		std::stringstream input("var a\n"
								"var a \n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();

		REQUIRE_THROWS_AS(calculatorController.HandleCommand(), IdentifierIsNotUniqueException);
	}
}

TEST_CASE("Test set variable value")
{
	SECTION("Test set existed variable success")
	{
		double value = 5;
		std::stringstream input("var a\n"
									"let a =5\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();

		REQUIRE(calculator.GetIdentifier("a")->GetValue() == value);
	}

	SECTION("Test set non existed variable success")
	{
		double value = 5;
		std::stringstream input("let a = 5\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();

		REQUIRE(calculator.GetIdentifier("a")->GetValue() == value);
	}

	SECTION("Test set variable by another variable success")
	{
		double value = 5;
		std::stringstream input("let a=5\n"
								    "let b =a\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();

		REQUIRE(calculator.GetIdentifier("b")->GetValue() == value);
	}
}

TEST_CASE("Test set function value")
{
	SECTION("Test set function by variable success")
	{
		double value = 5;
		std::stringstream input("let a=5\n"
									"fn b =a\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();

		REQUIRE(calculator.GetIdentifier("b")->GetValue() == value);
	}

	SECTION("Test set function by variable expression success")
	{
		double value = 74;
		std::stringstream input("let a=5\n"
									"let b =69\n"
									"fn x = a+b\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();

		REQUIRE(calculator.GetIdentifier("x")->GetValue() == value);
	}

	SECTION("Test set function by function expression success")
	{
		double value = 10;
		std::stringstream input("let a=5\n"
								"let b =69\n"
								"fn x1 = a + b\n"
								"fn x2 = a - b\n"
								"fn x = x1+x2\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();

		REQUIRE(calculator.GetIdentifier("x")->GetValue() == value);
	}

	SECTION("Test set function by existed identifier fail")
	{
		std::stringstream input("let a=5\n"
								"let b =69\n"
								"fn a = a + b\n"
								"fn x = x1+x2\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		REQUIRE_THROWS_AS(calculatorController.HandleCommand(), IdentifierIsNotUniqueException);
	}

	SECTION("Test function update after variable update success")
	{
		double value = 9;
		std::stringstream input("let a=5\n"
								"let b =69\n"
								"fn x = a + b\n"
								"let b = 4\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		REQUIRE(calculator.GetIdentifier("x")->GetValue() == value);
	}
}

TEST_CASE("Test get identifier value")
{
	SECTION("Test get existed variable identifier success")
	{
		double value = 5;
		std::stringstream input("let a=5\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		REQUIRE(calculator.GetIdentifier("a")->GetValue() == value);
	}

	SECTION("Test get existed function identifier success")
	{
		double value = 74;
		std::stringstream input("let a=5\n"
								"let b =69\n"
								"fn x = a + b\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		REQUIRE(calculator.GetIdentifier("x")->GetValue() == value);
	}

	SECTION("Test get non existed identifier success")
	{
		std::stringstream input("let a=5\n"
								"let b =69\n"
								"fn x = a + b\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		REQUIRE_THROWS_AS(calculator.GetIdentifier("xyz")->GetValue(), UndeclaredIdentifierException);
	}
}

TEST_CASE("Test get variables success")
{
	SECTION("Test get existed variables success")
	{
		std::stringstream input("let a=5\n"
								"let b =69\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		auto variables = calculator.GetVariables();
		REQUIRE(variables["a"] == 5);
		REQUIRE(variables["b"] == 69);
	}

	SECTION("Test get empty variables success")
	{
		std::stringstream input;
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		auto variables = calculator.GetVariables();
		REQUIRE(variables.empty());
	}
}


TEST_CASE("Test get functions success")
{
	SECTION("Test get existed functions success")
	{
		double x1Value = 74;
		double x2Value = -64;
		std::stringstream input("let a=5\n"
								"let b =69\n"
								"fn x1 = a + b\n"
								"fn x2 = a - b\n");
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		calculatorController.HandleCommand();
		auto functions = calculator.GetFunctions();
		REQUIRE(functions["x1"] == x1Value);
		REQUIRE(functions["x2"] == x2Value);
	}

	SECTION("Test get empty functions success")
	{
		std::stringstream input;
		std::stringstream output;

		Calculator calculator;
		CalculatorController calculatorController(calculator, input, output);
		auto variables = calculator.GetFunctions();
		REQUIRE(variables.empty());
	}
}