#include "Rectangle.h"
#include <cmath>
#include <stdexcept>


void AssertEdgeIsValid(double edge)
{
	if (edge < 0)
	{
		throw std::invalid_argument("Edge can not be negative");
	}
}

Rectangle::Rectangle(Point leftTop, Point rightBottom, uint32_t fillColor, uint32_t outlineColor)
	: SolidShape(fillColor, outlineColor)
	, m_leftTop(leftTop)
	, m_width(std::abs(rightBottom.x - leftTop.x))
	, m_height(std::abs(leftTop.y - rightBottom.y))
{
}

Rectangle::Rectangle(Point leftTop, double width, double height, uint32_t fillColor, uint32_t outlineColor)
	: SolidShape(fillColor, outlineColor)
	, m_leftTop(leftTop)
{
	AssertEdgeIsValid(width);
	AssertEdgeIsValid(height);
	m_width = width;
	m_height = height;
}

double Rectangle::GetArea() const
{
	return m_width * m_height;
}

double Rectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

double Rectangle::GetWidth() const
{
	return m_width;
}

double Rectangle::GetHeight() const
{
	return m_height;
}


Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return Point(m_leftTop.x + m_width, m_leftTop.y + m_height);
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point leftBottom(m_leftTop.x, m_leftTop.y + m_height);
	Point rightTop(m_leftTop.x + m_width, m_leftTop.y);
	Point rightBottom(m_leftTop.x + m_width, m_leftTop.y + m_height);
	std::vector<Point> points = {m_leftTop, rightTop, rightBottom, leftBottom};

	canvas.FillPolygon(points, SolidShape::GetFillColor());
}

std::string Rectangle::ToString() const
{
	return SolidShape::ToString() +
		   "Width: " + std::to_string(m_width) + '\n' +
		   "Height: " + std::to_string(m_height) + '\n' +
		   "Left top: (" + std::to_string(m_leftTop.x) + ", " + std::to_string(m_leftTop.y) + ")\n" +
		   "Right bottom: (" + std::to_string(m_leftTop.x + m_width) + ", " + std::to_string(m_leftTop.y + m_height) + ")\n";
}