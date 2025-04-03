#include "Car.h"
#include "../Exception/Exception.h"


Car::Car()
	: m_isTurnedOn(false)
	, m_gear(0)
	, m_speed(0)
	, m_direction(0)
{
}

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

int Car::GetDirection() const
{
	return m_direction;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;
	return m_isTurnedOn;
}

bool Car::TurnOffEngine()
{
	AssertCarIsStanding();

	m_isTurnedOn = false;
	m_direction = m_standing;
	return true;
}

bool Car::SetGear(int gear)
{
	AssertGearIsInRange(gear);
	AssertCanSetGear(gear);
	AssertGearInSpeedRange(gear);

	if (gear == -1)
	{
		AssertBackwardIsAvailable();
	}
	AssertCanIncreaseGear(gear);

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	AssertSpeedIsNotNegative(speed);
	AssertCanSetSpeed();
	AssertNonAcceleration(speed);
	AssertSpeedInGearRange(speed);

	if (speed > 0)
	{
		if (m_gear == -1)
		{
			m_direction = m_backwardDirection;
		}
		else
		{
			m_direction = m_forwardDirection;
		}
	}
	else
	{
		m_direction = m_standing;
	}
	m_speed = speed;
	return true;
}

void Car::AssertCarIsStanding() const
{
	if (m_gear != 0 || m_speed != 0)
	{
		throw FailedToEngineOffWhileMovingException();
	}
}

void Car::AssertGearIsInRange(int gear) const
{
	if (m_minGear > gear || gear > m_maxGear)
	{
		throw GearIsOutOfRangeException();
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
	auto speedLimits = m_gearSpeedRanges.at(gear);
	if (speedLimits.first > m_speed || m_speed > speedLimits.second)
	{
		throw WrongCurrentSpeedException();
	}
}

void Car::AssertBackwardIsAvailable() const
{
	if (m_direction != m_backwardDirection && m_speed != 0)
	{
		throw FailedToReverseWhileMovingException();
	}
}

void Car::AssertSpeedIsNotNegative(int speed)
{
	if (speed < 0)
	{
		throw NegativeSpeedException();
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
	auto currentGearSpeedLimits = m_gearSpeedRanges.at(m_gear);
	if (currentGearSpeedLimits.first > speed || speed > currentGearSpeedLimits.second)
	{
		throw SpeedIsOutOfRangeException();
	}
}

void Car::AssertCanIncreaseGear(int gear) const
{
	if (gear > 0 && m_speed > 0 and m_direction == m_backwardDirection)
	{
		throw FailedToIncreaseGearException();
	}
}