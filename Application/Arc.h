#pragma once
#include "Shape.h"

class Arc : public Shape
{
public:

	Arc();

	Arc(const Point& center, double radius, double startAngle, double arcWidth, const string& strokeColor, const string& fillColor);
	
	Arc(const Arc& other) = default;

	Arc& operator = (const Arc &other) = default;

	~Arc() = default;

public:

	virtual void printShapeData() const override;

	virtual void translate(const Point& vec) override;

	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

public:

	Point getCenter() const { return center; }

	double getRadius() const { return radius; }

	double getStartAngle() const { return startAngle; }

	double getArcWidth() const { return arcWidth; }

	void setCenter(const Point& center) { this->center = center; }

	void setRadius(double radius);

	void setStartAngle(double startAngle) { this->startAngle = startAngle; }

	void setArcWidth(double arcWidth);

private:

	Point center;
	double radius;
	double startAngle;
	double arcWidth;
};


class ArcCreator : public ShapeCreator
{
public:

	ArcCreator() : ShapeCreator("arc") {}
	virtual Shape* createShape(string& line) const override;
	virtual Shape* createShape(vector<string>& shapeParameters) const override;
};