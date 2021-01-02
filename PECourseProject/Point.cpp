#include <math.h>
#include <iostream>
#include "Point.h"

Point::Point(): x(0), y(0)
{}

Point::Point(int x, int y) :x(x), y(y)
{}

double Point::distanceTo(Point other)
{
	return sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2));
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	os << point.x << " " << point.y << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Point& point)
{
	is >> point.x >> point.y;
	return is;
}
