#include <catch2/catch_all.hpp>
#include "fakeit.hpp"
#include "../Canvas/ICanvas.h"
#include "../Model/Circle.h"



TEST_CASE("Test drawing")
{
	fakeit::Mock<ICanvas> mock;

	Point center(10, 20);
	fakeit::When(Method(mock, DrawCircle)).Do(
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