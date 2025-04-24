#include "Shape.h"


Shape::Shape(uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

uint32_t Shape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string Shape::ToString() const
{
	return "Area: " + std::to_string(GetArea()) + '\n' +
			"Perimeter: " + std::to_string(GetPerimeter()) + '\n' +
		    "Outline color: " + std::to_string(Shape::GetOutlineColor()) + '\n';
}

IShape::~IShape() = default;