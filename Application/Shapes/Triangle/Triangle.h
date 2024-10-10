#pragma once
#include "Shape.h"
#include <vector>

class Triangle : public Shape
{
public:
	Triangle();

	Triangle(const Point& a, const Point& b, const Point& c, const string& strokeColor, const string& fillColor);

	Triangle& operator=(const Triangle& other) = default;

	Triangle(const Triangle& other) = default;

	~Triangle() = default;

public:

	virtual void printShapeData() const override;

	virtual void translate(const Point& vec) override;

	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

private:
	Point a;
	Point b;
	Point c;

private:

	Point getCenter();
};

class TriangleCreator : public ShapeCreator
{
public:

	TriangleCreator() : ShapeCreator("triangle") {}
	virtual Shape* createShape(string& line) const override;
	virtual Shape* createShape(vector<string>& shapeParameters) const override;
};