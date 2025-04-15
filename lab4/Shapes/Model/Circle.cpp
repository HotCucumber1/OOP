#include "Circle.h"
#include <cmath>
#include <stdexcept>

void AssertRadiusIsValid(double radius)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Radius can not be negative");
	}
}

Circle::Circle(Point center, double radius, uint32_t fillColor, uint32_t outlineColor)
	: SolidShape(fillColor, outlineColor)
	, m_center(center)
{
	AssertRadiusIsValid(radius);
	m_radius = radius;
}

double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}

std::string Circle::ToString() const
{
	// TODO: вынести
	return "Area: " + std::to_string(GetArea()) + '\n' +
		   "Perimeter: " + std::to_string(GetPerimeter()) + '\n' +
		   "Radius: " + std::to_string(m_radius) + '\n' +
		   "Center: (" + std::to_string(m_center.x) + ", " + std::to_string(m_center.y) + ")\n" +
		   "Outline color: " + std::to_string(m_outlineColor) + '\n' +
		   "Fill color: " + std::to_string(m_fillColor) + '\n';
}