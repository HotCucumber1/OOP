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
	, m_width(std::abs(rightBottom.x - leftTop.x))
	, m_height(std::abs(leftTop.y - rightBottom.y))
{
	if (leftTop.x < rightBottom.x)
	{
		m_leftTop = leftTop;
	}
	else
	{
		m_leftTop = rightBottom;
	}
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

std::string Rectangle::ToString() const
{
	return "Area: " + std::to_string(GetArea()) + '\n' +
		   "Perimeter: " + std::to_string(GetPerimeter()) + '\n' +
		   "Width: " + std::to_string(m_width) + '\n' +
		   "Height: " + std::to_string(m_height) + '\n' +
		   "Outline color: " + std::to_string(m_outlineColor) + '\n' +
		   "Fill color: " + std::to_string(m_fillColor) + '\n' +
		   "Left top: (" + std::to_string(m_leftTop.x) + ", " + std::to_string(m_leftTop.y) + ")\n" +
		   "Right bottom: (" + std::to_string(m_leftTop.x + m_width) + ", " + std::to_string(m_leftTop.y + m_height) + ")\n";
}