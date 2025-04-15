#include "LineSegment.h"
#include <cmath>


LineSegment::LineSegment(Point startPoint, Point endPoint, uint32_t color)
	: Shape(color)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
{
}

double LineSegment::GetArea() const
{
	return 0;
}

double LineSegment::GetPerimeter() const
{
	return GetLength(m_startPoint, m_endPoint);
}

Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}

std::string LineSegment::ToString() const
{
	return "Area: " + std::to_string(GetArea()) + '\n' +
		   "Perimeter: " + std::to_string(GetPerimeter()) + '\n' +
		   "Outline color: " + std::to_string(m_outlineColor) + '\n' +
		   "Start point: (" + std::to_string(m_startPoint.x) + ", " + std::to_string(m_startPoint.y) + ")\n" +
		   "End point: (" + std::to_string(m_endPoint.x) + ", " + std::to_string(m_endPoint.y) + ")\n";
}