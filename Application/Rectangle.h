#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:

	Rectangle();

	Rectangle(const Rectangle& other) = default;

	Rectangle& operator=(const Rectangle& other) = default;

	Rectangle(Point TL, double height, double width, string stroke, string fill);

public:

	virtual void printShapeData() const override;

	virtual void translate(const Point& vec) override;

	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

public:

	Point getTL() const { return TL; }

	double getWidth() const { return width; }

	double getHeight() const { return height; }

	void setHeight(double height) { this->height = height; }

	void setWidth(double width) { this->width = width; }

private:

	Point TL;
	double height;
	double width;
};

class RectCreator : public ShapeCreator
{
public:

	RectCreator() : ShapeCreator("rect") {}
	virtual Shape* createShape(string& line) const override;
	virtual Shape* createShape(vector<string>& shapeParameters) const override;
};
