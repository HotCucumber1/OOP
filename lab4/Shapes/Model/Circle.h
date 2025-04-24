#pragma once
#include "SolidShape.h"
#include "Point.h"

class Circle : public SolidShape
{
public:
	Circle(Point center, double radius, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;
	Point GetCenter() const;
	double GetRadius() const;

private:
	Point m_center;
	double m_radius;
};
