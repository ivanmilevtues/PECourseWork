#include <math.h>
#include <iostream>
#include "Point.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

double Point::distanceTo(Point other)
{
	return sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2));
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
	os << point.x << " " << point.y << std::endl;
	return os;
}
