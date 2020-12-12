#include <vector>
#include "Point.h"

class Route
{
public:
	Route();

	void addPoint(Point point);
	void removePoint(Point point);
	int getLength();

private:
	std::vector<Point> points;
	int numberOfDailyDrives;
};