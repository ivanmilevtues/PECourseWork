#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Point.h"

Point::Point(): x(0), y(0)
{}

Point::Point(double x, double y) :x(x), y(y)
{}

double Point::distanceTo(Point other)
{
	const long radius = 6371;
	double lat1 = this->x * M_PI / 180;
	double lat2 = other.x * M_PI / 180;
	double dlat = (other.x - this->x) * M_PI / 180;
	double dlon = (other.y - this->y) * M_PI / 180;

	double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));

	return radius * c;
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
