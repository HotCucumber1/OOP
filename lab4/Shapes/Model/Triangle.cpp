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

	auto perimeter = firstEdge + secondEdge + thirdEdge;

	return std::sqrt(perimeter * (perimeter - firstEdge) * (perimeter - secondEdge) * (perimeter - thirdEdge));
}


std::string Triangle::ToString() const
{
	return "Area: " + std::to_string(GetArea()) + '\n' +
		   "Perimeter: " + std::to_string(GetPerimeter()) + '\n' +
		   "Outline color: " + std::to_string(m_outlineColor) + '\n' +
		   "Fill color: " + std::to_string(m_fillColor) + '\n' +
		   "First vertex: (" + std::to_string(m_vertex1.x) + ", " + std::to_string(m_vertex1.y) + ")\n" +
		   "Second vertex: (" + std::to_string(m_vertex2.x) + ", " + std::to_string(m_vertex2.y) + ")\n" +
		   "Third vertex: (" + std::to_string(m_vertex3.x) + ", " + std::to_string(m_vertex3.y) + ")\n";
}