#pragma once
#include "Shape.h"
#include <vector>

using std::vector;

class Polygon : public Shape
{
public:

	Polygon() = default;

	Polygon(const vector<Point>& points, const string& strokeColor, const string& fillColor);

	Polygon(const Polygon& other) = default;

	Polygon& operator=(const Polygon& other) = default;

public:

	virtual void printShapeData() const override;

	virtual void translate(const Point& vec) override;

	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

private:

	vector<Point> vertex;

	Point getCenter() const;
};

class PolygonCreator : public ShapeCreator
{
public:

	PolygonCreator() : ShapeCreator("polygon") {}
	virtual Shape* createShape(string& line) const override;
	virtual Shape* createShape(vector<string>& shapeParameters) const override;
};