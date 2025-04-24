#pragma once
#include "../Canvas/ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
};