#pragma once

class Point
{
public:

	Point(double x, double y);

	Point();

	Point(const Point& other) = default;

	Point& operator=(const Point& other) = default;

	~Point() = default;

	Point operator-();

public:

	void translate(const Point& vec);

	void setX(double x) { this->x = x; }

	void setY(double y) { this->y = y; }

	double getX() const { return x; }

	double getY() const { return y; }

	bool isInRegion(const Point& TL, const Point& BR) const;

private:

	double x;
	double y;

};
