#pragma once
#include "IShape.h"

class Shape : public virtual IShape
{
public:
	explicit Shape(uint32_t outlineColor);
	uint32_t GetOutlineColor() const final;

protected:
	uint32_t m_outlineColor;
};
