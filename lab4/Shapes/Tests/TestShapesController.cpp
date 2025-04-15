#include <catch2/catch_all.hpp>
#include "../Controller/ShapeController.h"
#include <iostream>

TEST_CASE("Test ShapeController")
{
	SECTION("Test calculate min and max shapes success")
	{
		std::istringstream input(
			"line_segment 1 2 2 2 000000\n"
			"312\n"
			"rectangle 10 10 30 30 000000 111111\n"
			"triangle 10 10 20 20 20 10 111111 FFFFFF\n"
			"circle 0 0 100 AAAAAA BBBBBB\n"
		);
		// TODO: неверные параметры
		double lineLength = 1;
		double rectangleArea = 400;
		double circleArea = M_PI * 100 * 100;
		std::stringstream output;
		ShapeController shapeController(input, output);

		// line
		shapeController.ReadShape();
		auto maxAreaShape = shapeController.GetMaxAreaShape();
		auto minPerimeterShape = shapeController.GetMinPerimeterShape();
		REQUIRE(maxAreaShape->GetArea() == 0);
		REQUIRE(minPerimeterShape->GetPerimeter() == lineLength);

		// 312
		REQUIRE_THROWS_AS(shapeController.ReadShape(), std::runtime_error);

		//rectangle
		shapeController.ReadShape();
		maxAreaShape = shapeController.GetMaxAreaShape();
		minPerimeterShape = shapeController.GetMinPerimeterShape();
		REQUIRE(maxAreaShape->GetArea() == rectangleArea);
		REQUIRE(minPerimeterShape->GetPerimeter() == lineLength);

		// triangle
		shapeController.ReadShape();
		maxAreaShape = shapeController.GetMaxAreaShape();
		minPerimeterShape = shapeController.GetMinPerimeterShape();
		REQUIRE(maxAreaShape->GetArea() == rectangleArea);
		REQUIRE(minPerimeterShape->GetPerimeter() == lineLength);

		// circle
		shapeController.ReadShape();
		maxAreaShape = shapeController.GetMaxAreaShape();
		minPerimeterShape = shapeController.GetMinPerimeterShape();
		REQUIRE(maxAreaShape->GetArea() == circleArea);
		REQUIRE(minPerimeterShape->GetPerimeter() == lineLength);
	}
}