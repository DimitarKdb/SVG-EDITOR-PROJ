#include "Rectangle.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

Rectangle::Rectangle()
	: Rectangle(Point(0, 0), 0, 0, "none", "none")
{}

Rectangle::Rectangle(Point TL, double height, double width, string stroke, string fill)
	: Shape(ShapeTypes::RECTANGLE), TL(TL), height(height), width(width)
{
	this->stroke = stroke;
	this->fill = fill;
}

void Rectangle::printShapeData() const
{
	if (isHidden())
		return;

	cout << "Rectangle: id: " << this->id << ", TL: " << "(" << TL.getX() << ", " << TL.getY() << ")"
		<< ", width: " << width << ", height: " << height
		<< " stroke color: " << stroke << ", fill color: " << fill << endl;
}

void Rectangle::translate(const Point& vec)
{
	TL.translate(vec);
}

void Rectangle::scale(double wCoeff, double hCoeff)
{
	width *= wCoeff;
	height *= hCoeff;
}

bool Rectangle::isInRegion(Point TL, Point BR) const
{
	Point rectBR;

	double rectBrX = this->TL.getX() + width;
	double rectBrY = this->TL.getY() - height;

	rectBR.setX(rectBrX);
	rectBR.setY(rectBrY);

	return (TL.isInRegion(TL, BR) && rectBR.isInRegion(TL, BR));
}

string Rectangle::serialize()
{
	//<rect x="20" y="20" width="60" height="40" stroke="black" fill="orange"/>
	
	string serialized = "";

	serialized += "<rect x=\"";
	serialized += to_string(TL.getX());
	serialized += "\" y=\"";
	serialized += to_string(TL.getY());
	serialized += "\" width=\"";
	serialized += to_string(height);
	serialized += "\" height=\"";
	serialized += to_string(height);
	serialized += "\" stroke=\"";
	serialized += stroke;
	serialized += "\" fill=\"";
	serialized += fill;
	serialized += "\"/>";

	return serialized;
}

Shape* Rectangle::clone()
{
	return new Rectangle(*this);
}

Shape* RectCreator::createShape(string& line) const
{
	//<rect x="20" y="20" width="60" height="40" stroke="black" fill="orange"/>
	int xPos = line.find("x=");
	int yPos = line.find("y=");
	int wPos = line.find("width=");
	int hPos = line.find("height=");
	int strokePos = line.find("stroke=");
	int fillPos = line.find("fill=");

	xPos += 3;
	double x = stod(line.substr(xPos, yPos - 2));

	yPos += 3;
	double y = stod(line.substr(yPos, wPos - 2));

	wPos += 7;
	double width = stod(line.substr(wPos, hPos - 2));

	hPos += 8;
	double height = stod(line.substr(hPos, strokePos - 2));

	strokePos += 8;
	string strokeColor = line.substr(strokePos, (fillPos - strokePos - 2));

	fillPos += 6;
	string fillColor = line.substr(fillPos, line.size() - fillPos - 3);

	return new Rectangle(Point(x, y), height, width, strokeColor, fillColor);
}

Shape* RectCreator::createShape(vector<string>& shapeParameters) const
{
	if (shapeParameters.size() != 6)
		return nullptr;

	double xCoord = stod(shapeParameters[0]);
	double yCoord = stod(shapeParameters[1]);
	double width = stod(shapeParameters[2]);
	double height = stod(shapeParameters[3]);

	string stroke = shapeParameters[4];
	string fill = shapeParameters[5];

	return new Rectangle(Point(xCoord, yCoord), height, width, stroke, fill);
}

static RectCreator __;
