#include "Ellipse.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

Ellipse::Ellipse()
	:Ellipse(Point(0, 0), 0, 0, "null", "null")
{}

Ellipse::Ellipse(const Point& center, double xRadius, double yRadius, const string& strokeColor, const string& fillColor)
	:Shape(ShapeTypes::ELLIPSE), center(center), xRadius(xRadius), yRadius(yRadius)
{
	this->stroke = strokeColor;
	this->fill = fillColor;
}

void Ellipse::printShapeData() const
{

	if (isHidden())
		return;

	cout << "Ellipse: id: " << this->id << ", center: " << "(" << center.getX() << ", " << center.getY() << ")"
		<< ", xRadius:" << xRadius << ", yRadius:" << yRadius
		<< ", stroke color: " << stroke << ", fill color: " << fill << endl;

}

void Ellipse::translate(const Point& vec)
{
	center.translate(vec);
}

void Ellipse::scale(double wCoeff, double hCoeff)
{
	xRadius *= wCoeff;
	yRadius *= hCoeff;
}

bool Ellipse::isInRegion(Point TL, Point BR) const
{
	return center.isInRegion(TL, BR);
}

string Ellipse::serialize()
{
	string serialized = "";

	serialized += "<ellipse cx=\"";
	serialized += to_string(center.getX());
	serialized += "\" cy=\"";
	serialized += to_string(center.getY());
	serialized += "\" rx=\"";
	serialized += to_string(xRadius);
	serialized += "\" ry=\"";
	serialized += to_string(yRadius);
	serialized += "\" stroke=\"";
	serialized += stroke;
	serialized += "\" fill=\"";
	serialized += fill;
	serialized += "\"/>";

	return serialized;
}

Shape* Ellipse::clone()
{
	return new Ellipse(*this);
}

Shape* EllipseCreator::createShape(string& line) const
{
	//<ellipse cx="10" cy="10" rx="190" ry="10" stroke="black" fill="red"/>

	int x1pos = line.find("cx=");
	int y1pos = line.find("cy=");
	int xRadPos = line.find("rx=");
	int yRadPos = line.find("ry=");
	int strokePos = line.find("stroke=");
	int fillPos = line.find("fill=");

	x1pos += 4;
	double x1 = stod(line.substr(x1pos, y1pos - 2));

	y1pos += 4;
	double y1 = stod(line.substr(y1pos, xRadPos - 2));

	xRadPos += 4;
	double xRadius = stod(line.substr(xRadPos, yRadPos - 2));

	yRadPos += 4;
	double yRadius = stod(line.substr(yRadPos, strokePos - 2));

	strokePos += 8;
	string strokeColor = line.substr(strokePos, fillPos - strokePos - 2);

	fillPos += 6;
	string fillColor = line.substr(fillPos, line.size() - fillPos - 3);

	return new Ellipse(Point(x1, y1), xRadius, yRadius, strokeColor, fillColor);;
}

Shape* EllipseCreator::createShape(vector<string>& shapeParameters) const
{
	if (shapeParameters.size() != 6)
		return nullptr;

	double xCenter = stod(shapeParameters[0]);
	double yCenter = stod(shapeParameters[1]);

	double xRad = stod(shapeParameters[2]);
	double yRad = stod(shapeParameters[3]);

	string strokeColor = shapeParameters[4];
	string fillColor = shapeParameters[5];


	return new Ellipse(Point(xCenter, yCenter), xRad, yRad, strokeColor, fillColor);
}

static EllipseCreator __;
