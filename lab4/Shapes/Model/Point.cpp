#include "Point.h"
#include <cmath>


double GetLength(Point startPoint, Point endPoint)
{
	return std::sqrt(
		std::pow(endPoint.x - startPoint.x, 2) + std::pow(endPoint.y - startPoint.y, 2)
	);
}