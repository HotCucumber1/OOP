#include "Shape.h"


Shape::Shape(uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{
}

uint32_t Shape::GetOutlineColor() const
{
	return m_outlineColor;
}

IShape::~IShape() = default;