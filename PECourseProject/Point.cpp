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
	const long radius = 6371000;
	double f1 = this->x * M_PI / 180;
	double f2 = other.x * M_PI / 180;
	double df = (other.x - this->x) * M_PI / 180;
	double dlam = (other.y - this->y) * M_PI / 180;

	double a = sin(df / 2) * sin(df / 2) + cos(f1) * cos(f2) * sin(dlam / 2) * sin(dlam / 2);
	double c = atan2(sqrt(a), sqrt(1 - a));

	return radius * c / 1000; // return in KM
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
