#pragma once
#include "IShape.h"

class Shape : public virtual IShape // TODO: почитать!!!!
{
public:
	explicit Shape(uint32_t outlineColor);
	uint32_t GetOutlineColor() const final;

protected: // TODO: remove
	uint32_t m_outlineColor;
};
