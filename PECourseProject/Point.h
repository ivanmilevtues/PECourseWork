class Point
{
public:
	Point(int x, int y);

	int distanceTo(Point other);
private:
	int x, y;
};