#include "Route.h"
#include <iostream>

Route::Route():numberOfDailyDrives(0), name("")
{}

Route::Route(std::string name): name(name)
{}

void Route::addPoint(Point point) {
	this->points.push_back(point);
}

void Route::removePoint(Point point) {
	// TODO: FIXME
}

int Route::getLength() {
	int length = 0;
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

std::ostream& operator<<(std::ostream& os, const Route& route)
{
	os << route.name << " " << route.numberOfDailyDrives << " " << std::endl;
	for (std::vector<Point>::const_iterator it = route.points.begin(); it != route.points.end(); it++) {
		os << *it;
	}
	return os;
}