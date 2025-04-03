#pragma once
#include <unordered_map>

class Car
{
public:
	Car();
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

	bool IsTurnedOn() const;
	int GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	void AssertGearIsValid(int gear) const;
	void AssertSpeedIsValid(int speed) const;
	void AssertCarIsStanding() const;
	void AssertGearIsInRange(int gear) const;
	void AssertCanSetGear(int gear) const;
	void AssertCanSetSpeed() const;
	void AssertBackwardIsAvailable() const;
	void AssertNonAcceleration(int speed) const;
	void AssertSpeedInGearRange(int speed) const;
	void AssertGearInSpeedRange(int gear) const;
	void AssertCanIncreaseGear(int gear) const;
	static void AssertSpeedIsNotNegative(int speed);

private:
	int m_speed;
	int m_gear;
	bool m_isTurnedOn;
	int m_direction;

	const int m_minGear = -1;
	const int m_maxGear = 5;
	const int m_forwardDirection = 1;
	const int m_backwardDirection = -1;
	const int m_standing = 0;

	const std::unordered_map<int, std::pair<int, int>> m_gearSpeedRanges = {
		{-1, {0, 20}},
		{0, {0, 150}},
		{1, {0, 30}},
		{2, {20, 50}},
		{3, {30, 60}},
		{4, {40, 90}},
		{5, {50, 150}},
	};
};
