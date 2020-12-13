#pragma once

class Point
{
public:
	Point(int x, int y);

	double distanceTo(Point other);
private:
	int x, y;
};