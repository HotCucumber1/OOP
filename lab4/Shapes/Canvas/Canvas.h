#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>


class Canvas : public ICanvas
{
public:
	explicit Canvas(sf::RenderWindow& window);
	void DrawLine(const Point& from, const Point& to, uint32_t lineColor) override;
	void FillPolygon(const std::vector<Point>& points, uint32_t fillColor) override;
	void DrawCircle(const Point& center, double radius, uint32_t lineColor) override;
	void FillCircle(const Point& center, double radius, uint32_t fillColor) override;

private:
	sf::RenderWindow& m_window;
};
