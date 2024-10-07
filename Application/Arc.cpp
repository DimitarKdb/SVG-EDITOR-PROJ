#include "Arc.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::to_string;

Arc::Arc() : Arc(Point(0,0), 0, 0, 0, "none", "none")
{}

Arc::Arc(const Point & center, double radius, double startAngle, double arcWidth, const string & strokeColor, const string & fillColor)
	: Shape(ShapeTypes::ARC), center(center), startAngle(startAngle)
{
	setRadius(radius);
	setArcWidth(arcWidth);
	stroke = strokeColor;
	fill = fillColor;
}

void Arc::printShapeData() const
{
	if (isHidden())
		return;

	cout << "Arc: id: " << this->id << ", Center: " << "(" << center.getX() << ", " << center.getY() << ")"
		<< ", radius: " << radius << ", start angle: " << startAngle << "deg, arc width: " << arcWidth
		<< "deg, stroke color: " << stroke << ", fill color: " << fill << endl;
}

void Arc::translate(const Point& vec)
{
	this->center.translate(vec);
}

void Arc::scale(double wCoeff, double hCoeff)
{
	radius *= wCoeff;
}

bool Arc::isInRegion(Point TL, Point BR) const
{
	Point arcTL{ center.getX() - radius, center.getY() + radius };
	Point arcBR{ center.getX() + radius, center.getY() - radius };

	return (arcTL.isInRegion(TL, BR) && arcBR.isInRegion(TL,BR));
}

string Arc::serialize()
{
	//<arc x="10" y="20" rad="10" start="120" width="240" stroke="black" fill="orange"\>
	
	string serialized = "";

	serialized += "<arc x=\"";
	serialized += to_string(center.getX());
	serialized += "\" y=\"";
	serialized += to_string(center.getY());
	serialized += "\" rad=\"";
	serialized += to_string(radius);
	serialized += "\" start=\"";
	serialized += to_string(startAngle);
	serialized += "\" width=\"";
	serialized += to_string(arcWidth);
	serialized += "\" stroke=\"";
	serialized += stroke;
	serialized += "\" fill=\"";
	serialized += fill;
	serialized += "\"/>";

	return serialized;
}

Shape* Arc::clone()
{
	return new Arc(*this);
}

void Arc::setRadius(double radius)
{
	if (radius < 0)
		throw std::invalid_argument("Radius cannot be negative");

	this->radius = radius;
}

void Arc::setArcWidth(double arcWidth)
{
	if (abs(arcWidth) >= 360) {
		this->arcWidth = 360;
	}
	
	this->arcWidth = arcWidth;

}

Shape* ArcCreator::createShape(string& line) const
{
	//<arc x="10" y="20" rad="10" start="120" width="240" stroke="black" fill="orange"\>
	int xPos = line.find("x=");
	int yPos = line.find("y=");
	int rPos = line.find("rad=");
	int stPos = line.find("start=");
	int wPos = line.find("width=");
	int strokePos = line.find("stroke=");
	int fillPos = line.find("fill=");

	xPos += 3;
	double x = stod(line.substr(xPos, yPos - 2));

	yPos += 3;
	double y = stod(line.substr(yPos, wPos - 2));

	rPos += 5;
	double radius = stod(line.substr(rPos, stPos - 2));

	stPos += 7;
	double start = stod(line.substr(stPos, wPos - 2));

	wPos += 7;
	double width = stod(line.substr(wPos, strokePos - 2));

	strokePos += 8;
	string strokeColor = line.substr(strokePos, fillPos - strokePos - 2);

	fillPos += 6;
	string fillColor = line.substr(fillPos, line.length() - fillPos - 3);

	return new Arc(Point(x, y), radius, start, width, strokeColor, fillColor);
}

Shape* ArcCreator::createShape(vector<string>& shapeParameters) const
{
	if (shapeParameters.size() != 7)
		return nullptr;
	 
	double xCoord = stod(shapeParameters[0]);
	double yCoord = stod(shapeParameters[1]);

	double radius = stod(shapeParameters[2]);
	double start = stod(shapeParameters[3]);
	double width = stod(shapeParameters[4]);

	string strokeColor = shapeParameters[5];
	string fillColor = shapeParameters[6];

	return new Arc(Point(xCoord, yCoord), radius, start, width, strokeColor, fillColor);
}


static ArcCreator __;