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