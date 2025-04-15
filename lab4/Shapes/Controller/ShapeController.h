#pragma once
#include "../Model/IShape.h"
#include <functional>
#include <sstream>
#include <vector>
#include <memory>

class ShapeController
{
public:
	ShapeController(std::istream& input, std::ostream& output);
	void ReadShape();
	IShape* GetMaxAreaShape() const;
	IShape* GetMinPerimeterShape() const;

private:
	void ReadLineSegment(std::istream& args);
	void ReadTriangle(std::istream& args);
	void ReadRectangle(std::istream& args);
	void ReadCircle(std::istream& args);
	void AssertInputIsOpen() const;

	using Handler = std::function<void(std::istream& args)>;
	using ShapeHandlerMap = std::unordered_map<std::string, Handler>;

	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::istream& m_input;
	std::ostream& m_output;

	const ShapeHandlerMap m_shapeHandlerMap;
};
