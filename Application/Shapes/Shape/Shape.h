#pragma once
#include "Point.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

enum class ShapeTypes
{
	UNKNOWN = -1,

	BASE_SHAPE,
	ARC,
	LINE,
	POLYGON,
	RECTANGLE,
	GROUP,
	TRIANGLE,
	ELLIPSE,

	SHAPES_COUNT
};

class Shape
{
public:

	virtual void printShapeData() const = 0;

	virtual void translate(const Point& vec) = 0;

	virtual void scale(double wCoeff, double hCoeff) = 0;

	virtual bool isInRegion(Point TL, Point BR) const = 0;

	virtual string serialize() = 0;

	virtual Shape* clone() = 0;

	virtual void insertIn(Shape* const shapePtr);

	virtual void ungroup(int id = -1);

	virtual void changeVisibility() { hidden = !hidden; }

public:

	Shape(const ShapeTypes type);

	virtual ~Shape() = default;

	Shape(const Shape& other);

	Shape& operator=(const Shape& other) = default;

public:

	bool isHidden() const { return hidden; }

	bool isGrouped() const { return grouped; }

	void changeGroupedState() { grouped = !grouped; }

	void setGroupId(int id);

	int getGroupId() const { return groupId; }

	int getShapeId() const { return id; }

	string getStrokeColor() const { return stroke; }

	string getFillColor() const { return fill; }

	ShapeTypes getType() const;

	string getTypeAsStr() const;

	void setStrokeColor(const string color) { this->stroke = color; }

	void setFillColor(const string color) { this->fill = color; }

	static void resetObjectId() { objectID = 1; }

protected:

	static size_t objectID;

	size_t id = 0;
	int groupId = -1;

	bool hidden = 0;
	bool grouped = 0;

	string stroke = "null";
	string fill = "null";

	ShapeTypes type = ShapeTypes::BASE_SHAPE;
};


class ShapeCreator
{
public:

	ShapeCreator(string shape);

	virtual ~ShapeCreator() = default;

	string getShapeName() const { return shapeName; }

	virtual Shape* createShape(string& line) const = 0;

	virtual Shape* createShape(vector<string>& parameters) const = 0;

protected:
	
	string shapeName;
};


