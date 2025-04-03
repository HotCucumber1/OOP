#include "CarController.h"
#include "../Exception/Exception.h"


CarController::CarController(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_commandMap({
		  {"Info", [this](std::istream& stream) { return Info(stream); }},
		  {"EngineOn", [this](std::istream& stream) { return EngineOn(stream); }},
		  {"EngineOff", [this](std::istream& stream) { return EngineOff(stream); }},
		  {"SetGear", [this](std::istream& stream) { return SetGear(stream); }},
		  {"SetSpeed", [this](std::istream& stream) { return SetSpeed(stream); }},
	  })
{
	AssertInputIsOpen();
}

bool CarController::HandleCommand()
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
		return commandIt->second(stream);
	}
	catch (const std::exception& exception)
	{
		m_output << exception.what() << std::endl;
		return false;
	}
}

bool CarController::Info(std::istream&)
{
	std::string engineState = m_car.IsTurnedOn()
		? "on"
		: "off";
	std::string direction =
		(m_car.GetDirection() == -1) ? "backward" :
		(m_car.GetDirection() == 0) ? "standing still" :
		"forward";

	m_output << "Engine: " << engineState << std::endl
			<< "Direction: " << direction << std::endl
			<< "Speed: " << m_car.GetSpeed() << std::endl
			<< "Gear: " << m_car.GetGear() << std::endl;

	return true;
}

bool CarController::EngineOn(std::istream&)
{
	return m_car.TurnOnEngine();
}

bool CarController::EngineOff(std::istream&)
{
	return m_car.TurnOffEngine();
}

bool CarController::SetGear(std::istream& input)
{
	int gear;
	try
	{
		input >> gear;
	}
	catch (const std::exception& exception)
	{
		m_output << exception.what() << std::endl;
		return false;
	}
	return m_car.SetGear(gear);
}

bool CarController::SetSpeed(std::istream& input)
{
	int speed;
	try
	{
		input >> speed;
	}
	catch (const std::exception& exception)
	{
		throw InvalidCommandArgumentException();
	}
	return m_car.SetSpeed(speed);
}

void CarController::AssertInputIsOpen()
{
	if (m_input.fail())
	{
		throw WrongInputException();
	}
}