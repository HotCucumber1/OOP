#include <catch2/catch_all.hpp>
#include "../Model/Car.h"
#include "../Exception/Exception.h"

TEST_CASE("Test turning on")
{
	SECTION("Turn on success")
	{
		Car car;
		car.TurnOnEngine();
		REQUIRE(car.IsTurnedOn());
	}
}

TEST_CASE("Test turning off")
{
	SECTION("Turn off success")
	{
		Car car;
		car.TurnOnEngine();
		car.TurnOffEngine();
		REQUIRE(!car.IsTurnedOn());
	}

	SECTION("Turn off with non zero gear failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		REQUIRE_THROWS_AS(car.TurnOffEngine(), FailedToEngineOffWhileMovingException);
	}

	SECTION("Turn off with non zero speed failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		REQUIRE_THROWS_AS(car.TurnOffEngine(), FailedToEngineOffWhileMovingException);
	}
}

TEST_CASE("Test setting gear")
{
	SECTION("Increase gear while standing success")
	{
		const int gear = 1;

		Car car;
		car.TurnOnEngine();
		car.SetGear(gear);
		REQUIRE(car.GetGear() == gear);
	}

	SECTION("Set backward gear while standing success")
	{
		const int gear = -1;

		Car car;
		car.TurnOnEngine();
		car.SetGear(gear);
		REQUIRE(car.GetGear() == gear);
	}

	SECTION ("Set neutral gear while moving success")
	{
		const int neutralGear = 0;
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(neutralGear);
		REQUIRE(car.GetGear() == neutralGear);
	}

	SECTION("Increase gear while moving success")
	{
		const int secondGear = 2;
		Car car;
		car.TurnOnEngine();
		car.SetGear(secondGear - 1);
		car.SetSpeed(20);
		car.SetGear(secondGear);
		REQUIRE(car.GetGear() == secondGear);
	}

	SECTION("Decrease gear while moving success")
	{
		const int firstGear = 1;
		Car car;
		car.TurnOnEngine();
		car.SetGear(firstGear);
		car.SetSpeed(20);
		car.SetGear(firstGear + 1);
		car.SetGear(firstGear);
		REQUIRE(car.GetGear() == firstGear);
	}

	SECTION("Set too low gear failed")
	{
		Car car;
		car.TurnOnEngine();
		REQUIRE_THROWS_AS(car.SetGear(-5), GearIsOutOfRangeException);
	}

	SECTION("Set too high gear failed")
	{
		Car car;
		car.TurnOnEngine();
		REQUIRE_THROWS_AS(car.SetGear(6), GearIsOutOfRangeException);
	}

	SECTION("Set gear while engine turned off failed")
	{
		Car car;
		REQUIRE_THROWS_AS(car.SetGear(1), EngineIsOffException);
	}

	SECTION("Set gear while speed too low failed")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		REQUIRE_THROWS_AS(car.SetGear(1), WrongCurrentSpeedException);
	}

	SECTION("Set gear while speed too high failed")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		REQUIRE_THROWS_AS(car.SetGear(1), WrongCurrentSpeedException);
	}

	SECTION("Set gear while speed too low failed")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE_THROWS_AS(car.SetGear(2), WrongCurrentSpeedException);
	}

	SECTION("Set forward gear while moving backward success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		REQUIRE_THROWS_AS(car.SetGear(1), FailedToIncreaseGearException);
	}

	SECTION("Set backward gear while moving forward failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		REQUIRE_THROWS_AS(car.SetGear(-1), FailedToReverseWhileMovingException);
	}
}

TEST_CASE("Test setting speed")
{
	SECTION("Set forward speed success")
	{
		const int speed = 10;
		const int forward = 1;

		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(speed);
		REQUIRE(car.GetSpeed() == speed);
		REQUIRE(car.GetDirection() == forward);
	}

	SECTION("Set backward speed success")
	{
		const int speed = 10;
		const int backward = -1;

		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(speed);
		REQUIRE(car.GetSpeed() == speed);
		REQUIRE(car.GetDirection() == backward);
	}

	SECTION("Stop success")
	{
		const int speed = 0;
		const int standing = 0;

		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);
		car.SetSpeed(0);

		REQUIRE(car.GetSpeed() == speed);
		REQUIRE(car.GetDirection() == standing);
	}

	SECTION("Set negative speed failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		REQUIRE_THROWS_AS(car.SetSpeed(-20), NegativeSpeedException);
	}

	SECTION("Set speed with engine turn off failure")
	{
		Car car;
		REQUIRE_THROWS_AS(car.SetSpeed(20), FailedToSetSpeedWhileEngineOffException);
	}

	SECTION("Accelerate speed on neutral from forward failure")
	{
		const int startSpeed = 20;

		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(startSpeed);
		car.SetGear(0);

		REQUIRE_THROWS_AS(car.SetSpeed(startSpeed + 5), FailedToAccelerateException);
	}

	SECTION("Set too low speed for current gear failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		REQUIRE_THROWS_AS(car.SetSpeed(10), SpeedIsOutOfRangeException);
	}

	SECTION("Set too high speed for current gear failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		REQUIRE_THROWS_AS(car.SetSpeed(50), SpeedIsOutOfRangeException);
	}

	SECTION("Accelerate on neutral from backward failure")
	{
		const int startSpeed = 15;

		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(startSpeed);
		car.SetGear(0);

		REQUIRE_THROWS_AS(car.SetSpeed(startSpeed + 5), FailedToAccelerateException);
	}

	SECTION("Decrease speed while moving backward on neutral success")
	{
		const int speed = 10;

		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(20);
		car.SetGear(0);
		car.SetSpeed(speed);

		REQUIRE(car.GetSpeed() == speed);
	}
	
	SECTION("Backward gear excess speed lower limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		REQUIRE_THROWS_AS(car.SetSpeed(100), SpeedIsOutOfRangeException);
	}

	SECTION("Backward gear speed limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(20);
		REQUIRE(car.GetSpeed() == 20);
	}

	SECTION("First gear excess speed upper limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		REQUIRE_THROWS_AS(car.SetSpeed(100), SpeedIsOutOfRangeException);
	}

	SECTION("First gear speed upper limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		REQUIRE(car.GetSpeed() == 30);
	}

	SECTION("Second gear excess speed lower limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		REQUIRE_THROWS_AS(car.SetSpeed(10), SpeedIsOutOfRangeException);
	}

	SECTION("Second gear speed lower limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(20);
		REQUIRE(car.GetSpeed() == 20);
	}

	SECTION("Second gear excess speed upper limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		REQUIRE_THROWS_AS(car.SetSpeed(100), SpeedIsOutOfRangeException);
	}

	SECTION("Second gear speed upper limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		REQUIRE(car.GetSpeed() == 50);
	}

	SECTION("Third gear excess speed lower limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		REQUIRE_THROWS_AS(car.SetSpeed(20), SpeedIsOutOfRangeException);
	}

	SECTION("Third gear speed lower limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(30);
		REQUIRE(car.GetSpeed() == 30);
	}

	SECTION("Third gear excess speed upper limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		REQUIRE_THROWS_AS(car.SetSpeed(100), SpeedIsOutOfRangeException);
	}

	SECTION("Third gear speed upper limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		REQUIRE(car.GetSpeed() == 60);
	}

	SECTION("Fourth gear excess speed lower limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		REQUIRE_THROWS_AS(car.SetSpeed(30), SpeedIsOutOfRangeException);
	}

	SECTION("Fourth gear speed lower limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		car.SetSpeed(40);
		REQUIRE(car.GetSpeed() == 40);
	}

	SECTION("Fourth gear excess speed upper limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		REQUIRE_THROWS_AS(car.SetSpeed(100), SpeedIsOutOfRangeException);
	}

	SECTION("Fourth gear speed upper limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		car.SetGear(4);
		car.SetSpeed(90);
		REQUIRE(car.GetSpeed() == 90);
	}

	SECTION("Fifth gear excess speed lower limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		car.SetSpeed(60);
		car.SetGear(5);
		REQUIRE_THROWS_AS(car.SetSpeed(40), SpeedIsOutOfRangeException);
	}

	SECTION("Fifth gear speed lower limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		car.SetSpeed(60);
		car.SetGear(5);
		car.SetSpeed(50);
		REQUIRE(car.GetSpeed() == 50);
	}

	SECTION("Fifth gear excess speed upper limit failure")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		car.SetSpeed(60);
		car.SetGear(5);
		REQUIRE_THROWS_AS(car.SetSpeed(200), SpeedIsOutOfRangeException);
	}

	SECTION("Fifth gear speed upper limit success")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		car.SetGear(4);
		car.SetSpeed(90);
		car.SetGear(5);
		car.SetSpeed(150);
		REQUIRE(car.GetSpeed() == 150);
	}
}