#include "Triangle.h"
#include <cmath>


Triangle::Triangle(Point vertex1, Point vertex2, Point vertex3, uint32_t fillColor, uint32_t outlineColor)
	: SolidShape(fillColor, outlineColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

double Triangle::GetPerimeter() const
{
	auto firstEdge = GetLength(m_vertex1, m_vertex2);
	auto secondEdge = GetLength(m_vertex1, m_vertex3);
	auto thirdEdge = GetLength(m_vertex2, m_vertex3);

	return firstEdge + secondEdge + thirdEdge;
}

double Triangle::GetArea() const
{
	auto firstEdge = GetLength(m_vertex1, m_vertex2);
	auto secondEdge = GetLength(m_vertex1, m_vertex3);
	auto thirdEdge = GetLength(m_vertex2, m_vertex3);

	auto halfPerimeter = 0.5 * (firstEdge + secondEdge + thirdEdge);

	return std::sqrt(halfPerimeter * (halfPerimeter - firstEdge) * (halfPerimeter - secondEdge) * (halfPerimeter - thirdEdge));
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}

std::string Triangle::ToString() const
{
	return SolidShape::ToString() +
		   "First vertex: (" + std::to_string(m_vertex1.x) + ", " + std::to_string(m_vertex1.y) + ")\n" +
		   "Second vertex: (" + std::to_string(m_vertex2.x) + ", " + std::to_string(m_vertex2.y) + ")\n" +
		   "Third vertex: (" + std::to_string(m_vertex3.x) + ", " + std::to_string(m_vertex3.y) + ")\n";
}

void Triangle::Draw(ICanvas& canvas) const
{
	std::vector<Point> points{m_vertex1, m_vertex2, m_vertex3};
	canvas.FillPolygon(points, SolidShape::GetFillColor());
}