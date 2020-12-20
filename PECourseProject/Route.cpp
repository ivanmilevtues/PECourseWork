#include "Route.h"

Route::Route() {}

Route::Route(std::string name) {
	this->name = name;
}

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
