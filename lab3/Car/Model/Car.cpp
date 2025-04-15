#include "Car.h"
#include "../Exception/Exception.h"
#include <unordered_map>

using SpeedRanges = std::unordered_map<int, std::pair<int, int>>;

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const SpeedRanges GEAR_SPEED_RANGES = {
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
};

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

int Car::GetDirection() const
{
	switch (m_direction)
	{
	case Direction::ForwardDirection:
		return 1;
	case Direction::Standing:
		return 0;
	case Direction::BackwardDirection:
		return -1;
	}
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

void Car::TurnOnEngine()
{
	m_isTurnedOn = true;
}

void Car::TurnOffEngine()
{
	AssertCarIsStanding();
	m_isTurnedOn = false;
}

void Car::SetGear(int gear)
{
	AssertGearIsValid(gear);

	if (gear == -1)
	{
		AssertBackwardIsAvailable();
	}
	AssertForwardIsAvailable(gear);

	m_gear = gear;
}

void Car::SetSpeed(int speed)
{
	AssertSpeedIsValid(speed);

	if (speed > 0)
	{
		if (m_gear == -1)
		{
			m_direction = Direction::BackwardDirection;
		}
		else
		{
			m_direction = Direction::ForwardDirection;
		}
	}
	else
	{
		m_direction = Direction::Standing;
	}
	m_speed = speed;
}

void AssertGearIsInRange(int gear)
{
	if (MIN_GEAR > gear || gear > MAX_GEAR)
	{
		throw GearIsOutOfRangeException();
	}
}

void Car::AssertGearIsValid(int gear) const
{
	AssertGearIsInRange(gear);
	AssertCanSetGear(gear);
	AssertGearInSpeedRange(gear);
}

void AssertSpeedIsNotNegative(int speed)
{
	if (speed < 0)
	{
		throw NegativeSpeedException();
	}
}

void Car::AssertSpeedIsValid(int speed) const
{
	AssertSpeedIsNotNegative(speed);
	AssertCanSetSpeed();
	AssertNonAcceleration(speed);
	AssertSpeedInGearRange(speed);
}

void Car::AssertCarIsStanding() const
{
	if (m_gear != 0 || m_speed != 0)
	{
		throw FailedToEngineOffWhileMovingException();
	}
}

void Car::AssertCanSetGear(int gear) const
{
	if (!m_isTurnedOn && gear != 0)
	{
		throw EngineIsOffException();
	}
}

void Car::AssertGearInSpeedRange(int gear) const
{
	auto speedLimits = GEAR_SPEED_RANGES.at(gear);
	if (speedLimits.first > m_speed || m_speed > speedLimits.second)
	{
		throw WrongCurrentSpeedException();
	}
}

void Car::AssertBackwardIsAvailable() const
{
	if (m_direction != Direction::BackwardDirection && m_speed != 0)
	{
		throw FailedToReverseWhileMovingException();
	}
}

void Car::AssertCanSetSpeed() const
{
	if (!m_isTurnedOn)
	{
		throw FailedToSetSpeedWhileEngineOffException();
	}
}

void Car::AssertNonAcceleration(int speed) const
{
	if (m_gear == 0 && speed > m_speed)
	{
		throw FailedToAccelerateException();
	}
}

void Car::AssertSpeedInGearRange(int speed) const
{
	auto currentGearSpeedLimits = GEAR_SPEED_RANGES.at(m_gear);
	if (currentGearSpeedLimits.first > speed || speed > currentGearSpeedLimits.second)
	{
		throw SpeedIsOutOfRangeException();
	}
}

void Car::AssertForwardIsAvailable(int gear) const
{
	if (m_direction == Direction::BackwardDirection &&
		gear > 0 &&
		m_speed > 0
	)
	{
		throw FailedToIncreaseGearException();
	}
}