#include "Line.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

Line::Line() : Line(Point(0, 0), Point(0, 0), "none")
{}

Line::Line(const Point& start, const Point& end, const string& color)
	: Shape(ShapeTypes::LINE), start(start), end(end)
{
	this->stroke = color;
}

void Line::printShapeData() const
{
	if (isHidden())
		return;

	cout << "Line: id: " << this->id << ", start: " << "(" << start.getX() << ", " << start.getY() << ")"
		 << ", end:" << "(" << end.getX() << ", " << end.getY() << ")"
		 << " stroke color: " << stroke << endl;
}

void Line::translate(const Point& vec)
{
	start.translate(vec);
	end.translate(vec);
}

void Line::scale(double wCoeff, double hCoeff)
{
	Point lineCenter;

	lineCenter.setX((start.getX() + end.getX()) / 2);
	lineCenter.setY((start.getY() + end.getY()) / 2);

	start.setX(start.getX() - lineCenter.getX());
	start.setY(start.getY() - lineCenter.getY());

	end.setX(end.getX() - lineCenter.getX());
	end.setY(end.getY() - lineCenter.getY());

	double startNewX = start.getX() * wCoeff + lineCenter.getX();
	double startNewY = start.getY() * hCoeff + lineCenter.getY();

	double endNewX = end.getX() * wCoeff + lineCenter.getX();
	double endNewY = end.getY() * hCoeff + lineCenter.getY();

	start.setX(startNewX);
	start.setY(startNewY);

	end.setX(endNewX);
	end.setY(endNewY);
}

bool Line::isInRegion(Point TL, Point BR) const
{
	return (start.isInRegion(TL, BR) && end.isInRegion(TL, BR));
}

string Line::serialize()
{
	string serialized = "";

	serialized += "<line x1=\"";
	serialized += to_string(start.getX());
	serialized += "\" y1=\"";
	serialized += to_string(start.getY());
	serialized += "\" x2=\"";
	serialized += to_string(end.getX());
	serialized += "\" y2=\"";
	serialized += to_string(end.getY());
	serialized += "\" stroke=\"";
	serialized += stroke;
	serialized += "\"/>";

	return serialized;

	//<line x1="10" y1="10" x2="190" y2="10" stroke="black"/>
}

Shape* Line::clone()
{
	return new Line(*this);
}

Shape* LineCreator::createShape(string& line) const {
	//<line x1="10" y1="10" x2="190" y2="10" stroke="black"/>

	int x1pos = line.find("x1=");
	int y1pos = line.find("y1=");
	int x2pos = line.find("x2=");
	int y2pos = line.find("y2=");
	int strokePos = line.find("stroke=");

	x1pos += 4;
	double x1 = stod(line.substr(x1pos, y1pos - 2));

	y1pos += 4;
	double y1 = stod(line.substr(y1pos, x2pos - 2));

	x2pos += 4;
	double x2 = stod(line.substr(x2pos, y2pos - 2));

	y2pos += 4;
	double y2 = stod(line.substr(y2pos, strokePos - 2));

	strokePos += 8;
	string strokeColor = line.substr(strokePos, line.size() - strokePos - 3);

	return new Line(Point(x1,y1), Point(x2, y2), strokeColor);
}

Shape* LineCreator::createShape(vector<string>& shapeParameters) const
{
	if (shapeParameters.size() != 5)
		return nullptr;

	double xStart = stod(shapeParameters[0]);
	double yStart = stod(shapeParameters[1]);

	double xEnd = stod(shapeParameters[2]);
	double yEnd = stod(shapeParameters[3]);

	string strokeColor = shapeParameters[4];


	return new Line(Point(xStart, yStart), Point(xEnd, yEnd), strokeColor);
}

static LineCreator __;