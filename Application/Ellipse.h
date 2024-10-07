#pragma once
#include "Shape.h"
#include <vector>

class Ellipse : public Shape
{
public:
	Ellipse();

	Ellipse(const Point& center, double xRadius, double yRadius, const string& strokeColor, const string& fillColor);

	Ellipse& operator=(const Ellipse& other) = default;

	Ellipse(const Ellipse& other) = default;

	~Ellipse() = default;

public:

	virtual void printShapeData() const override;

	virtual void translate(const Point& vec) override;

	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

private:

	Point center;
	double xRadius;
	double yRadius;

};

class EllipseCreator : public ShapeCreator
{
public:

	EllipseCreator() : ShapeCreator("ellipse") {}
	virtual Shape* createShape(string& line) const override;
	virtual Shape* createShape(vector<string>& shapeParameters) const override;
};