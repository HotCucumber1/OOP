#pragma once

class Car
{
private:
	enum class Direction
	{
		BackwardDirection,
		Standing,
		ForwardDirection,
	};
public:
	Car() = default;
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

	bool IsTurnedOn() const;
	int GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	void AssertCarIsStanding() const;
	void AssertCanSetSpeed() const;
	void AssertBackwardIsAvailable() const;
	void AssertGearIsValid(int gear) const;
	void AssertCanSetGear(int gear) const;
	void AssertGearInSpeedRange(int gear) const;
	void AssertForwardIsAvailable(int gear) const;
	void AssertSpeedIsValid(int speed) const;
	void AssertNonAcceleration(int speed) const;
	void AssertSpeedInGearRange(int speed) const;

private:
	int m_speed = 0;
	int m_gear = 0;
	bool m_isTurnedOn = false;
	Direction m_direction = Direction::Standing;
};
