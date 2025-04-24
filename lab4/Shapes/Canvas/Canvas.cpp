#include "Canvas.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Canvas::Canvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void Canvas::DrawLine(const Point& from, const Point& to, uint32_t lineColor)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(from.x, from.y);
	line[0].color = sf::Color(lineColor);

	line[1].position = sf::Vector2f(to.x, to.y);
	line[1].color = sf::Color(lineColor);

	m_window.draw(line);
}

void Canvas::DrawCircle(const Point& center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(radius);

	circle.setOutlineColor(sf::Color::Magenta);
	circle.setPosition(center.x, center.y);
	circle.setOrigin(radius, radius);

	m_window.draw(circle);
}

void Canvas::FillCircle(const Point& center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(radius);

	circle.setFillColor(sf::Color(fillColor));
	circle.setPosition(center.x, center.y);
	circle.setOrigin(radius, radius);

	m_window.draw(circle);
}

void Canvas::FillPolygon(const std::vector<Point>& points, uint32_t fillColor)
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());

	for (int i = 0; i < points.size(); i++)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	polygon.setFillColor(sf::Color(fillColor));

	m_window.draw(polygon);
}
