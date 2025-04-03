#pragma once
#include "../Model/Car.h"
#include <functional>
#include <optional>
#include <sstream>

class CarController
{
public:
	CarController(Car& car, std::istream& input, std::ostream& output);
	void HandleCommand();
private:
	void Info(std::istream& args);
	void EngineOn(std::istream& args);
	void EngineOff(std::istream& args);
	void SetGear(std::istream& args);
	void SetSpeed(std::istream& args);
	void AssertInputIsOpen();

private:
	using Handler = std::function<void(std::istream& args)>;
	using CommandMap = std::unordered_map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const CommandMap m_commandMap;
};

