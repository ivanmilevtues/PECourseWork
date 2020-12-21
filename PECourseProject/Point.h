#pragma once

class Point
{
public:
	Point(int x, int y);

	double distanceTo(Point other);

	friend std::ostream& operator<<(std::ostream& os, const Point& point);
private:
	int x, y;
};