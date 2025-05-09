#pragma once
#include "ISolidShape.h"
#include "Shape.h"

class SolidShape : public Shape, public ISolidShape
{
public:
	SolidShape(uint32_t fillColor, uint32_t outlineColor);
	uint32_t GetFillColor() const final;
	std::string ToString() const override;

private:
	uint32_t m_fillColor;
};