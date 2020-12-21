#pragma once
#include <vector>
#include <string>
#include "Point.h"

class Route
{
public:
	Route();
	Route(std::string name);

	void addPoint(Point point);
	void removePoint(Point point);
	int getLength();
	std::string getName();

	friend std::ostream& operator<<(std::ostream& os, const Route& route);

private:
	std::vector<Point> points;
	int numberOfDailyDrives;
	std::string name;
};