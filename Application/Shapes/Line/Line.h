#pragma once
#include "Shape.h"

class Line : public Shape
{
public:

	Line();

	Line(const Point& start, const Point& end, const string& color);

	~Line() = default;

	Line(const Line& other) = default;

	Line& operator=(const Line& other) = default;

public:

	Point getStart() const { return start; }

	Point getEnd() const { return end; }

	void setStart(const Point& start) { this->start = start; }

	void setEnd(const Point& end) { this->end = end; }

public:

	virtual void printShapeData() const override;
	
	virtual void translate(const Point& vec) override;
	
	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

private:

	Point start;
	Point end;
};

class LineCreator : public ShapeCreator
{
public:

	LineCreator() : ShapeCreator("line") {}
	virtual Shape* createShape(string& line) const override;
	virtual Shape* createShape(vector<string>& shapeParameters) const override;
};

