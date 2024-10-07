#include "Polygon.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::to_string;

Polygon::Polygon(const vector<Point>& points, const string& strokeColor, const string& fillColor)
	: Shape(ShapeTypes::POLYGON), vertex(points)
{
	stroke = strokeColor;
	fill = fillColor;
}

void Polygon::printShapeData() const
{
	if (isHidden())
		return;

	cout << "Polygon: id: " << this->id << ", stroke color: " << stroke << ", fill color: " << fill << ", ";
	cout << "Vertices: ";

	for (size_t i = 0; i < vertex.size(); i++)
	{
		cout << "(" << vertex[i].getX() << ", " << vertex[i].getY() << ") ";
	}

	cout << endl;
}

void Polygon::translate(const Point& vec)
{
	for (size_t i = 0; i < vertex.size(); i++)
	{
		vertex[i].translate(vec);
	}
}

void Polygon::scale(double wCoeff, double hCoeff)
{
	Point center = getCenter();

	translate(-center);

	for (size_t i = 0; i < vertex.size(); i++)
	{
		vertex[i].setX(vertex[i].getX() * wCoeff);
		vertex[i].setY(vertex[i].getY() * hCoeff);
	}

	translate(center);
}

bool Polygon::isInRegion(Point TL, Point BR) const
{
	for (size_t i = 0; i < vertex.size(); i++)
	{
		if (!vertex[i].isInRegion(TL, BR)) {
			return false;
		}
	}

	return true;
}

string Polygon::serialize()
{
	//<polygon points="150,150 170,180 130,180 180,96" fill="red" stroke="black"/>
	string serialized = "";

	serialized += "<polygon points=\"";

	for (size_t i = 0; i < vertex.size(); i++)
	{
		if (i != 0) {
			serialized += " ";
		}

		((serialized += to_string(vertex[i].getX())) += ",") += to_string(vertex[i].getY());
	}

	serialized += "\" stroke=\"";
	serialized += stroke;
	serialized += "\" fill=\"";
	serialized += fill;
	serialized += "\"/>";

	return serialized;
}

Shape* Polygon::clone()
{
	return new Polygon(*this);
}

Point Polygon::getCenter() const
{
	Point center;
	int points = vertex.size();
	double xSum = 0;
	double ySum = 0;

	for (size_t i = 0; i < points; i++)
	{
		xSum += vertex[i].getX();
		ySum += vertex[i].getY();
	}

	xSum /= points;
	ySum /= points;

	center.setX(xSum);
	center.setY(ySum);

	return center;
}

vector<Point> extractPoints(const string& line, int initPosition, int endPos)
{
	string coordX;
	string coordY;
	vector<Point> points;
	bool readX = false;

	for (size_t i = initPosition; i < endPos; i++)
	{
		readX = false;
		while (true)
		{
			if (line[i] == ' ' || line[i] == '"') {
				points.push_back(Point(stod(coordX), stod(coordY)));
				break;
			}

			if (line[i] == ',') {
				readX = true;
				i++;
				continue;
			}

			if (!readX) {
				coordX.push_back(line[i]);
			}
			else {
				coordY.push_back(line[i]);
			}

			i++;
		}
		coordX.clear();
		coordY.clear();
	}

	return points;
}

Shape* PolygonCreator::createShape(string& line) const
{
	//<polygon points="150,150 170,180 130,180 180,96" stroke="black" fill="red"/>
	
	int pointsPos = line.find("points=");
	int strokePos = line.find("stroke=");
	int fillPos = line.find("fill=");
	pointsPos += 8;

	vector<Point> points = extractPoints(line, pointsPos, strokePos - 1);

	strokePos += 8;
	string stroke = line.substr(strokePos, fillPos - strokePos - 2);

	fillPos += 6;
	string fill = line.substr(fillPos, line.size() - fillPos - 3);

	return new Polygon(points, stroke, fill);
}

Shape* PolygonCreator::createShape(vector<string>& shapeParameters) const
{
	if (shapeParameters.size() % 2 != 0)
		return nullptr;

	vector<Point> points;
	int strokePos = shapeParameters.size() - 1;
	int fillPos = shapeParameters.size() - 2;

	for (size_t i = 0; i < shapeParameters.size() - 2; i += 2)
	{
		points.push_back(Point(stod(shapeParameters[i]), stod(shapeParameters[i + 1])));
	}

	string stroke = shapeParameters[strokePos];

	string fill = shapeParameters[fillPos];

	return new Polygon(points, stroke, fill);
}

static PolygonCreator __;
