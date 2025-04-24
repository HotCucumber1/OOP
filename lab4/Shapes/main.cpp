#include "Controller/ShapeController.h"
#include <iostream>

int main()
{
	try
	{
		ShapeController shapeController(std::cin, std::cout);
		bool inputEnd = false;
		while (!inputEnd)
		{
			shapeController.ReadShape();
			if (std::cin.eof())
			{
				inputEnd = true;
			}
		}

		auto maxAreaShape = shapeController.GetMaxAreaShape();
		auto minPerimeterShape = shapeController.GetMinPerimeterShape();

		std::cout << "Фигура с максимальной площадью: " << std::endl
				  << maxAreaShape->ToString() << std::endl;
		std::cout << "Фигура с минимальным периметром: " << std::endl
			      << minPerimeterShape->ToString() << std::endl;

		shapeController.DrawShapes();
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	return 0;
}