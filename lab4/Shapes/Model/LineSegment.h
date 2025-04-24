#pragma once
#include "Shape.h"
#include "Point.h"

class LineSegment : public Shape
{
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t color);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

private:
	Point m_startPoint;
	Point m_endPoint;
};
