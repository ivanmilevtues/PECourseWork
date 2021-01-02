#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Point.h"

class Route
{
public:
	Route();
	Route(std::string name, int numberOfDailyDrives);

	void addPoint(Point point);
	double getLength();
	std::string getName();
	int getNumberOfDailyDrives();

	friend std::ostream& operator<<(std::ostream& os, const Route& route);
	friend std::ofstream& operator<<(std::ofstream& os, const Route& route);

	friend std::istream& operator>>(std::istream& is, Route& route);
private:
	std::vector<Point> points;
	int numberOfDailyDrives;
	std::string name;
};