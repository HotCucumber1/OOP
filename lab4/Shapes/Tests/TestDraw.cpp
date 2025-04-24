#include <catch2/catch_all.hpp>
#include "fakeit.hpp"
#include "../Canvas/ICanvas.h"
#include "../Model/Circle.h"



TEST_CASE("Test drawing circle")
{
	fakeit::Mock<ICanvas> mock;

	Point center(10, 20);
	fakeit::When(Method(mock, FillCircle)).Do(
		[](Point p, double radius, uint32_t fillColor) {
			REQUIRE(p.x == 10);
			REQUIRE(p.y == 20);
			REQUIRE(radius == 5);
			REQUIRE(fillColor == 11111111);
		}
	);

	Circle circle(center, 5, 11111111, 11111111);
	circle.Draw(mock.get());

	fakeit::Verify(Method(mock, FillCircle)).Once();
}

TEST_CASE("Test drawing line")
{
	fakeit::Mock<ICanvas> mock;

	Point start(10, 20);
	Point finish(20, 30);
	fakeit::When(Method(mock, DrawLine)).Do(
		[](Point start, Point finish, uint32_t fillColor) {
			REQUIRE(start.x == 10);
			REQUIRE(start.y == 20);
			REQUIRE(finish.x == 10);
			REQUIRE(finish.y == 20);
			REQUIRE(fillColor == 11111111);
		}
	);

	Circle circle(start, 5, 11111111, 11111111);
	circle.Draw(mock.get());

	fakeit::Verify(Method(mock, FillCircle)).Once();
}