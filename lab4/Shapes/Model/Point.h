#pragma once

class Point
{
public:
	Point(double x, double y)
		: x(x)
		, y(y)
	{
	}
	double x;
	double y;
};

double GetLength(Point startPoint, Point endPoint);