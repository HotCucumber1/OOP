#pragma once
#include "../Model/Car.h"
#include <functional>
#include <optional>
#include <sstream>

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);
	void AssertInputIsOpen();

private:
	using Handler = std::function<bool(std::istream& args)>;
	using CommandMap = std::unordered_map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const CommandMap m_commandMap;
};

