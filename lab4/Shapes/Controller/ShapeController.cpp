#include "ShapeController.h"
#include "../Model/Rectangle.h"
#include "../Model/LineSegment.h"
#include "../Model/Circle.h"
#include "../Model/Triangle.h"
#include <ranges>
#include <algorithm>


const int COLOR_RADIX = 16;

ShapeController::ShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_shapeHandlerMap({
		  {"line_segment", [this](std::istream& stream) { ReadLineSegment(stream); } },
		  {"triangle", [this](std::istream& stream) { ReadTriangle(stream); } },
		  {"rectangle", [this](std::istream& stream) { ReadRectangle(stream); } },
		  {"circle", [this](std::istream& stream) { ReadCircle(stream); } },
	  })
{
	AssertInputIsOpen();
}

void ShapeController::ReadShape()
{
	try
	{
		std::string commandLine;
		getline(m_input, commandLine);
		std::istringstream stream(commandLine);

		std::string shape;
		stream >> shape;

		auto shapeHandler = m_shapeHandlerMap.find(shape);
		if (shapeHandler == m_shapeHandlerMap.end())
		{
			throw std::runtime_error("Unknown shape");
		}
		shapeHandler->second(stream);
	}
	catch (const std::exception& exception)
	{
		m_output << exception.what() << std::endl;
	}
}

IShape* ShapeController::GetMaxAreaShape() const
{
	auto maxAreaShape = std::ranges::max_element(m_shapes, {}, [](auto& shape) {
		return shape->GetArea();
	});
	if (maxAreaShape == m_shapes.end())
	{
		throw std::runtime_error("You must enter at least one shape");
	}
	return maxAreaShape->get();
}

IShape* ShapeController::GetMinPerimeterShape() const
{
	auto minPerimeterShape = std::ranges::min_element(m_shapes, {}, [](auto& shape) {
		return shape->GetPerimeter();
	});
	if (minPerimeterShape == m_shapes.end())
	{
		throw std::runtime_error("You must enter at least one shape");
	}
	return minPerimeterShape->get();
}

void ShapeController::ReadLineSegment(std::istream& args)
{
	double startX;
	double startY;
	double endX;
	double endY;
	std::string hexColor;

	args >> startX >> startY >> endX >> endY >> hexColor;

	uint32_t color = std::stoul(hexColor, nullptr, COLOR_RADIX);
	m_shapes.emplace_back(std::make_unique<LineSegment>(
		Point(startX, startY),
		Point(endX, endY),
		color
	));
}

void ShapeController::ReadTriangle(std::istream& args)
{
	double vertex1X;
	double vertex1Y;
	double vertex2X;
	double vertex2Y;
	double vertex3X;
	double vertex3Y;
	std::string hexFillColor;
	std::string hexOutlineColor;

	args >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y >> hexFillColor >> hexOutlineColor;
	uint32_t fillColor = std::stoul(hexFillColor, nullptr, COLOR_RADIX);
	uint32_t outlineColor = std::stoul(hexOutlineColor, nullptr, COLOR_RADIX);

	m_shapes.emplace_back(std::make_unique<Triangle>(
		Point(vertex1X, vertex1Y),
		Point(vertex2X, vertex2Y),
		Point(vertex3X, vertex3Y),
		fillColor,
		outlineColor
	));
}

void ShapeController::ReadRectangle(std::istream& args)
{
	double leftTopX;
	double leftTopY;
	double rightBottomX;
	double rightBottomY;
	std::string hexFillColor;
	std::string hexOutlineColor;

	args >> leftTopX >> leftTopY >> rightBottomX >> rightBottomY >> hexFillColor >> hexOutlineColor;
	uint32_t fillColor = std::stoul(hexFillColor, nullptr, COLOR_RADIX);
	uint32_t outlineColor = std::stoul(hexOutlineColor, nullptr, COLOR_RADIX);

	m_shapes.emplace_back(std::make_unique<Rectangle>(
		Point(leftTopX, leftTopY),
		Point(rightBottomX, rightBottomY),
		fillColor,
		outlineColor
	));
}

void ShapeController::ReadCircle(std::istream& args)
{
	double centerX;
	double centerY;
	double radius;
	std::string hexFillColor;
	std::string hexOutlineColor;

	args >> centerX >> centerY >> radius >> hexFillColor >> hexOutlineColor;
	uint32_t fillColor = std::stoul(hexFillColor, nullptr, COLOR_RADIX);
	uint32_t outlineColor = std::stoul(hexOutlineColor, nullptr, COLOR_RADIX);
	m_shapes.emplace_back(std::make_unique<Circle>(
		Point(centerX, centerY),
		radius,
		fillColor,
		outlineColor
	));
}

void ShapeController::AssertInputIsOpen() const
{
	if (m_input.fail())
	{
		throw std::runtime_error("Invalid input");
	}
}