#include "Point.h"

Point::Point(double x, double y) : x(x), y(y)
{}

Point::Point() : Point(0, 0)
{}

Point Point::operator-()
{
	return Point(-x, -y);
}

void Point::translate(const Point& vec)
{
	this->x += vec.x;
	this->y += vec.y;
}

bool Point::isInRegion(const Point& TL, const Point& BR) const
{

	if ((x >= TL.x && x <= BR.x) && (y <= TL.y && y >= BR.y))
		return true;

	return false;
}