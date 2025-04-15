#include "Controller/ShapeController.h"
#include <iostream>

int main()
{
	try
	{
		ShapeController shapeController(std::cin, std::cout);
		while (!std::cin.eof() || !std::cin.fail())
		{
			shapeController.ReadShape();
		}

		auto maxAreaShape = shapeController.GetMaxAreaShape();
		auto minPerimeterShape = shapeController.GetMinPerimeterShape();

		std::cout << "Фигура с максимальной площадью: " << std::endl
				  << maxAreaShape->ToString() << std::endl;
		std::cout << "Фигура с минимальным периметром: " << std::endl
			      << minPerimeterShape->ToString() << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}