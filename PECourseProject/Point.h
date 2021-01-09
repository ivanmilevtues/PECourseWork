#pragma once

class Point
{
public:
	// This constructor should be used only for creating dummy objects which will be populated via input stream, for everything else use the parametized constructor
	Point();
	Point(double x, double y);

	double distanceTo(Point other);

	friend std::ostream& operator<<(std::ostream& os, const Point& point);
	friend std::istream& operator>>(std::istream& os, Point& point);
private:
	float x, y;
};