#include "Route.h"
#include <iostream>

Route::Route():numberOfDailyDrives(0), name("")
{}

Route::Route(std::string name, int numberOfDailyDrives): name(name), numberOfDailyDrives(numberOfDailyDrives)
{}

void Route::addPoint(Point point) {
	this->points.push_back(point);
}

double Route::getLength() {
	double length = 0;
	Point prevPoint = points.at(0);
	for (std::vector<Point>::iterator pointIt = ++this->points.begin(); pointIt != this->points.end(); pointIt++) {
		length += prevPoint.distanceTo(*pointIt);
		prevPoint = *pointIt;
	}
	return length;
}

std::string Route::getName() {
	return this->name;
}

int Route::getNumberOfDailyDrives()
{
	return numberOfDailyDrives;
}

std::ostream& operator<<(std::ostream& os, const Route& route)
{
	os << route.name << " " << route.numberOfDailyDrives << " " << std::endl;
	for (std::vector<Point>::const_iterator it = route.points.begin(); it != route.points.end(); it++) {
		os << *it;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Route& route)
{
	is >> route.name >> route.numberOfDailyDrives;
	return is;
}

std::ofstream& operator<<(std::ofstream& os, const Route& route)
{
	os << "Route:" << std::endl << route.name << " " << route.numberOfDailyDrives << " " << std::endl;
	for (std::vector<Point>::const_iterator it = route.points.begin(); it != route.points.end(); it++) {
		os << *it;
	}
	return os;
}