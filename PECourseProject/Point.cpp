#include <math.h>
#include "Point.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Point::distanceTo(Point other)
{
	return sqrt(pow(other.x - this->x, 2) + pow(other.y - this->y, 2));
}
