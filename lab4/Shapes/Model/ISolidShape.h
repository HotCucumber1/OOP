#pragma once
#include "IShape.h"


class ISolidShape : public virtual IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
