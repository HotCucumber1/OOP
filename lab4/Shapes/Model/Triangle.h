#pragma once
#include "SolidShape.h"
#include "Point.h"

class Triangle : public SolidShape
{
public:
	Triangle(Point vertex1, Point vertex2, Point vertex3, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
