#pragma once
#include "SolidShape.h"
#include "Point.h"

class Rectangle : public SolidShape
{
public:
	Rectangle(Point leftTop, Point rightBottom, uint32_t fillColor, uint32_t outlineColor);
	Rectangle(Point leftTop, double width, double height, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	Point m_leftTop{};
	double m_width;
	double m_height;
};
