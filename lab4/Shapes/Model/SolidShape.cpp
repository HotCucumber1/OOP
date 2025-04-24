#include "SolidShape.h"


SolidShape::SolidShape(uint32_t fillColor, uint32_t outlineColor)
	: Shape(outlineColor)
	, m_fillColor(fillColor)
{
}

uint32_t SolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string SolidShape::ToString() const
{
	return Shape::ToString() + "Fill color: " + std::to_string(SolidShape::GetFillColor()) + '\n';
}