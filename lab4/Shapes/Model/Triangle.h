#pragma once
#include "ISolidShape.h"
#include "Point.h"
#include "SolidShape.h"
#include "../Canvas/ICanvas.h"

class Triangle : public SolidShape
{
public:
	Triangle(Point vertex1, Point vertex2, Point vertex3, uint32_t fillColor, uint32_t outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
