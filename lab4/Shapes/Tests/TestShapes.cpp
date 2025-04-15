#include <catch2/catch_all.hpp>
#include "../Model/LineSegment.h"
#include "../Model/Rectangle.h"
#include "../Model/Triangle.h"
#include "../Model/Circle.h"


uint32_t color = 0xffffff;

TEST_CASE("Test line segment")
{
	SECTION("Create line segment success")
	{
		Point startPoint(1, 2);
		Point endPoint(3, 4);
		LineSegment lineSegment(startPoint, endPoint, color);

		REQUIRE(lineSegment.GetPerimeter() == GetLength(startPoint, endPoint));
		REQUIRE(lineSegment.GetArea() == 0);
		REQUIRE(lineSegment.GetStartPoint().x == startPoint.x);
		REQUIRE(lineSegment.GetStartPoint().y == startPoint.y);
		REQUIRE(lineSegment.GetEndPoint().x == endPoint.x);
		REQUIRE(lineSegment.GetEndPoint().y == endPoint.y);
	}

	SECTION("Create line segment with zero length success")
	{
		Point startPoint(0, 0);
		Point endPoint(0, 0);
		LineSegment lineSegment(startPoint, endPoint, color);

		REQUIRE(lineSegment.GetPerimeter() == 0);
		REQUIRE(lineSegment.GetArea() == 0);
		REQUIRE(lineSegment.GetStartPoint().x == startPoint.x);
		REQUIRE(lineSegment.GetStartPoint().y == startPoint.y);
		REQUIRE(lineSegment.GetEndPoint().x == endPoint.x);
		REQUIRE(lineSegment.GetEndPoint().y == endPoint.y);
	}

	SECTION("Create line segment negative point coords success")
	{
		Point startPoint(-5, -5);
		Point endPoint(5, 5);
		LineSegment lineSegment(startPoint, endPoint, color);

		REQUIRE(lineSegment.GetPerimeter() == GetLength(startPoint, endPoint));
		REQUIRE(lineSegment.GetArea() == 0);
		REQUIRE(lineSegment.GetStartPoint().x == startPoint.x);
		REQUIRE(lineSegment.GetStartPoint().y == startPoint.y);
		REQUIRE(lineSegment.GetEndPoint().x == endPoint.x);
		REQUIRE(lineSegment.GetEndPoint().y == endPoint.y);
	}
}

TEST_CASE("Test rectangle")
{
	SECTION("Create rectangle by points success")
	{
		Point topLeft(10, 10);
		Point bottomRight(20, 20);
		int perimeter = 40;
		int area = 100;
		int height = 10;
		int width = 10;
		Rectangle rect(topLeft, bottomRight, color, color);

		REQUIRE(rect.GetPerimeter() == perimeter);
		REQUIRE(rect.GetArea() == area);
		REQUIRE(rect.GetWidth() == width);
		REQUIRE(rect.GetHeight() == height);
		REQUIRE(rect.GetLeftTop().x == topLeft.x);
		REQUIRE(rect.GetLeftTop().y == topLeft.y);
		REQUIRE(rect.GetRightBottom().x == bottomRight.x);
		REQUIRE(rect.GetRightBottom().y == bottomRight.y);
	}

	SECTION("Create rectangle by width and height success")
	{
		Point topLeft(10, 10);
		Point bottomRight(20, 20);
		int perimeter = 40;
		int area = 100;
		int height = 10;
		int width = 10;
		Rectangle rect(topLeft, width, height, color, color);

		REQUIRE(rect.GetPerimeter() == perimeter);
		REQUIRE(rect.GetArea() == area);
		REQUIRE(rect.GetWidth() == width);
		REQUIRE(rect.GetHeight() == height);
		REQUIRE(rect.GetLeftTop().x == topLeft.x);
		REQUIRE(rect.GetLeftTop().y == topLeft.y);
		REQUIRE(rect.GetRightBottom().x == bottomRight.x);
		REQUIRE(rect.GetRightBottom().y == bottomRight.y);
	}

	SECTION("Create rectangle with negative width and height failed")
	{
		Point topLeft(10, 10);
		int height = -10;
		int width = -10;
		REQUIRE_THROWS_AS(Rectangle(topLeft, width, height, color, color), std::invalid_argument);
	}
}

TEST_CASE("Test triangle")
{
	SECTION("Create triangle success")
	{
		Point vertex1(0, 3);
		Point vertex2(4, 0);
		Point vertex3(0, 0);
		int perimeter = 12;
		int area = 6;

		Triangle triangle(vertex1, vertex2, vertex3, color, color);
		REQUIRE(triangle.GetArea() == area);
		REQUIRE(triangle.GetPerimeter() == perimeter);
		REQUIRE(triangle.GetVertex1().x == vertex1.x);
		REQUIRE(triangle.GetVertex1().y == vertex1.y);
		REQUIRE(triangle.GetVertex2().x == vertex2.x);
		REQUIRE(triangle.GetVertex2().y == vertex2.y);
		REQUIRE(triangle.GetVertex3().x == vertex3.x);
		REQUIRE(triangle.GetVertex3().y == vertex3.y);
	}
}

TEST_CASE("Test circle")
{
	SECTION("Create circle success")
	{
		Point center(0, 0);
		double radius = 10;
		double perimeter = 2 * M_PI * radius;
		double area = M_PI * radius * radius;

		Circle circle(center, radius, color, color);
		REQUIRE(circle.GetArea() == area);
		REQUIRE(circle.GetPerimeter() == perimeter);
		REQUIRE(circle.GetRadius() == radius);
	}

	SECTION("Create circle with negative radius fail")
	{
		Point center(0, 0);
		double radius = -10;

		REQUIRE_THROWS_AS(Circle(center, radius, color, color), std::invalid_argument);
	}
}