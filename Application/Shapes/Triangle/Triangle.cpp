#include "Triangle.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

Triangle::Triangle()
	: Triangle(Point(0, 0), Point(0, 0), Point(0, 0), "null", "null")
{
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c, const string& strokeColor, const string& fillColor)
	:Shape(ShapeTypes::TRIANGLE), a(a), b(b), c(c)
{
	this->stroke = strokeColor;
	this->fill = fillColor;
}

void Triangle::printShapeData() const
{
	if (isHidden())
		return;

	cout << "Triangle: id: " << this->id << ", A: " << "(" << a.getX() << ", " << a.getY() << ")"
		<< ", B: " << "(" << b.getX() << ", " << b.getY() << ")"
		<< ", C: " << "(" << c.getX() << ", " << c.getY() << ")"
		<< " stroke color: " << stroke << ", fill color: " << fill << endl;
}

void Triangle::translate(const Point& vec)
{
	a.translate(vec);
	b.translate(vec);
	c.translate(vec);
}

void Triangle::scale(double wCoeff, double hCoeff)
{
	Point center = getCenter();

	translate(-center);

	a.setX(a.getX() * wCoeff);
	a.setY(a.getY() * hCoeff);

	b.setX(b.getX() * wCoeff);
	b.setY(b.getY() * hCoeff);

	c.setX(c.getX() * wCoeff);
	c.setY(c.getY() * hCoeff);

	translate(center);

	return;
}

bool Triangle::isInRegion(Point TL, Point BR) const
{
	return a.isInRegion(TL, BR) && b.isInRegion(TL, BR) && c.isInRegion(TL, BR);
}

string Triangle::serialize()
{
	string serialized = "";

	serialized += "<triangle x1=\"";
	serialized += to_string(a.getX());
	serialized += "\" y1=\"";
	serialized += to_string(b.getY());
	serialized += "\" x2=\"";
	serialized += to_string(b.getX());
	serialized += "\" y2=\"";
	serialized += to_string(b.getY());
	serialized += "\" x3=\"";
	serialized += to_string(c.getX());
	serialized += "\" y3=\"";
	serialized += to_string(c.getY());
	serialized += "\" stroke=\"";
	serialized += stroke;
	serialized += "\" fill=\"";
	serialized += fill;
	serialized += "\"/>";

	return serialized;
}

Shape* Triangle::clone()
{
	return new Triangle(*this);
}

Point Triangle::getCenter()
{
	Point center;

	double xSum = 0;
	double ySum = 0;

	xSum += a.getX() + b.getX() + c.getX();
	ySum += a.getY() + b.getY() + c.getY();


	xSum /= 3;
	ySum /= 3;

	center.setX(xSum);
	center.setY(ySum);

	return center;
}

Shape* TriangleCreator::createShape(string& line) const
{
	//<triangle x1="10" y1="10" x2="190" y2="10" x3="190" y3="10" stroke="black" fill="red"/>

	int x1pos = line.find("x1=");
	int y1pos = line.find("y1=");
	int x2pos = line.find("x2=");
	int y2pos = line.find("y2=");
	int x3pos = line.find("x3=");
	int y3pos = line.find("y3=");
	int strokePos = line.find("stroke=");
	int fillPos = line.find("fill=");

	x1pos += 4;
	double x1 = stod(line.substr(x1pos, y1pos - 2));

	y1pos += 4;
	double y1 = stod(line.substr(y1pos, x2pos - 2));

	x2pos += 4;
	double x2 = stod(line.substr(x2pos, y2pos - 2));

	y2pos += 4;
	double y2 = stod(line.substr(y2pos, x3pos - 2));

	x3pos += 4;
	double x3 = stod(line.substr(x3pos, y3pos - 2));

	y3pos += 4;
	double y3 = stod(line.substr(y3pos, strokePos - 2));

	strokePos += 8;
	string strokeColor = line.substr(strokePos, fillPos - strokePos - 2);

	fillPos += 6;
	string fillColor = line.substr(fillPos, line.size() - fillPos - 3);
	

	return new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), strokeColor, fillColor);
}

Shape* TriangleCreator::createShape(vector<string>& shapeParameters) const
{
	if (shapeParameters.size() != 8)
		return nullptr;

	double xA = stod(shapeParameters[0]);
	double yA = stod(shapeParameters[1]);

	double xB = stod(shapeParameters[2]);
	double yB = stod(shapeParameters[3]);

	double xC = stod(shapeParameters[4]);
	double yC = stod(shapeParameters[5]);

	string strokeColor = shapeParameters[6];
	string fillColor = shapeParameters[7];


	return new Triangle(Point(xA, yA), Point(xB, yB), Point(xC, yC), strokeColor, fillColor);
}

static TriangleCreator __;
