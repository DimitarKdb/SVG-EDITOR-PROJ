#include "ObjectManager.h"
#include "ShapeFactory.h"
#include "Group.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::getline;

ObjectManager& ObjectManager::getInstance()
{
	static ObjectManager theManager;

	return theManager;
}

bool ObjectManager::createShape(const string& shapeType, vector<string>& shapeParameters)
{
	Shape* createdShape = ShapeFactory::getInstance().createShape(shapeType, shapeParameters);

	if (createdShape) {
		shapes.push_back(createdShape);
		return true;
	}
	
	return false;
}

bool ObjectManager::readShapes(const string& fileName)
{
	if (!shapes.empty()) {
		shapes.clear();
		Shape::resetObjectId();
	}

	string fileExtension = getExtension(fileName);

	if (fileExtension == ".svg")
		return(readSVG(fileName));
	else
		return(readTXT(fileName));

	return false;
}

bool ObjectManager::translateShape(int id, Point vec)
{
	Shape* shape = getShapeById(id);

	if (!shape || shape->isGrouped())
		return false;

	shape->translate(vec);

	return true;
}

bool ObjectManager::translateAll(Point vec)
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if(!shapes[i]->isGrouped())
			shapes[i]->translate(vec);
	}

	return true;
}

bool ObjectManager::scaleShape(size_t id, double wCoeff, double hCoeff)
{
	Shape* shape = getShapeById(id);

	if (!shape || shape->isGrouped())
		return false;

	shape->scale(wCoeff, hCoeff);

	return true;
}

bool ObjectManager::scaleAll(double wCoeff, double hCoeff)
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (!shapes[i]->isGrouped())
			shapes[i]->scale(wCoeff, hCoeff);
	}

	return true;
}

bool ObjectManager::saveAs(const string& fileName)
{

	string fileExtension = getExtension(fileName);

	if (fileExtension == ".svg")
		return(saveSVG(fileName));
	else
		return(saveTXT(fileName));

	return false;
}

void ObjectManager::print()
{
	int count = 1;
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->isHidden())
			continue;

		cout << count++ << ": ";
		shapes[i]->printShapeData();
	}
}

bool ObjectManager::showFigure(int id)
{
	Shape* shape = getShapeById(id);

	if (!shape || shape->isGrouped())
		return false;

	if(shape->isHidden())
		shape->changeVisibility();

	return true;
}

bool ObjectManager::hideFigure(int id)
{
	Shape* shape = getShapeById(id);

	if (!shape || shape->isGrouped())
		return false;

	if (!shape->isHidden())
		shape->changeVisibility();

	return true;
}

bool ObjectManager::group(Point TL, Point BR)
{
	bool anyInRegion = false;
	Group* group = nullptr;

	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (!shapes[i]->isGrouped() && shapes[i]->isInRegion(TL, BR)) {
			if (anyInRegion == false) {
				group = new Group;
				anyInRegion = true;
			}

			group->insertIn(shapes[i]);
		}
	}

	if (anyInRegion) {
		shapes.push_back(group);
		return true;
	}

	return false;
}

bool ObjectManager::ungroup(size_t id)
{
	Shape* group = nullptr;
	int index = -1;

	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->getShapeId() == id) {
			group = shapes[i];
			index = i;
			break;
		}
	}

	if (!group || index == -1)
		return false;

	if (group->getType() != ShapeTypes::GROUP || group->isGrouped() || group->isHidden())
		return false;

	group->ungroup();
	delete group;

	for (size_t i = index; i < shapes.size() - 1; i++)
	{
		shapes[i] = shapes[i + 1];
	}

	shapes.pop_back();

	return true;
}

bool ObjectManager::insert(size_t grId, size_t shapeId)
{
	if (grId == shapeId)
		return false;

	Shape* group = nullptr;
	Shape* shape = nullptr;

	group = getShapeById(grId);
	shape = getShapeById(shapeId);


	if (!group || !shape || group->getType() != ShapeTypes::GROUP)
		return false;

	if (shape->isGrouped() || group->isHidden())
		return false;

	group->insertIn(shape);

	return true;
}

bool ObjectManager::extract(size_t grId, size_t shapeId)
{
	Shape* group = nullptr;
	Shape* shape = nullptr;

	group = getShapeById(grId);
	shape = getShapeById(shapeId);

	if (!group || group->getType() != ShapeTypes::GROUP)
		return false;

	if (!shape->isGrouped())
		return false;

	group->ungroup(shapeId);

	return true;
}

bool ObjectManager::stroke(size_t shapeId, const string& newStrokeColor)
{
	Shape* shape = nullptr;

	shape = getShapeById(shapeId);

	if (!shape)
		return false;

	if (shape->isGrouped() || newStrokeColor.empty())
		return false;

	shape->setStrokeColor(newStrokeColor);

	return true;
}

bool ObjectManager::fill(size_t shapeId, const string& newFillColor)
{
	Shape* shape = nullptr;

	shape = getShapeById(shapeId);

	if (!shape)
		return false;

	if (shape->isGrouped() || newFillColor.empty())
		return false;

	shape->setFillColor(newFillColor);

	return true;
}

bool ObjectManager::readFile(const string& fileName, bool(*lineIsNotShape)(const string& fileName))
{
	ifstream inputFile(fileName);

	if (inputFile.is_open()) {

		string line;

		while (!inputFile.eof())
		{
			getline(inputFile, line);

			if (lineIsNotShape(line))
				continue;

			int startPos = line.find_first_of("<");

			if (startPos == std::string::npos) {
				throw std::runtime_error("The " + fileName + " file is not in the right format!");
			}

			line = line.substr(startPos);

			Shape* createdShape = ShapeFactory::getInstance().createShape(line);

			if (createdShape)
				shapes.push_back(createdShape);

		}
		inputFile.close();

		return true;
	}
	else
	{
		ofstream createFile(fileName);

		createFile.close();

		return true;
	}

	return false;
}

bool ObjectManager::readSVG(const string& fileName)
{
	bool(*lineIsNotShape)(const string & line) = [](const string& line)->bool {
		return (line.empty() || line.find("</svg>") != string::npos || line.find("<svg") != string::npos || line.find("<!--") != string::npos);
	};

	return readFile(fileName, lineIsNotShape);
	
}

bool ObjectManager::readTXT(const string& fileName)
{
	bool(*lineIsNotShape)(const string & line) = [](const string& line)->bool {
		return line.empty();
	};

	return readFile(fileName, lineIsNotShape);

}

void ObjectManager::saveToFile(ofstream& outputFile)
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (!shapes[i]->isHidden()) {

			outputFile << shapes[i]->serialize();
			outputFile << endl;

		}
	}
}

bool ObjectManager::saveSVG(const string& fileName)
{
	ofstream outputFile(fileName);

	if (outputFile.is_open()) {

		outputFile << "<svg width=\"50000\" height=\"50000\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;

		saveToFile(outputFile);

		outputFile << "</svg>" << endl;

		return true;
	}
	
	return false;
	
}

bool ObjectManager::saveTXT(const string& fileName)
{
	ofstream outputFile(fileName);

	if (outputFile.is_open()) {

		saveToFile(outputFile);

		return true;
	}

	return false;

}

string ObjectManager::getExtension(const string& fileName)
{
	int extensionPos = fileName.find_last_of(".");

	string fileExtension;

	if (extensionPos != std::string::npos)
		fileExtension = fileName.substr(extensionPos, fileName.size() - extensionPos);

	return fileExtension;
}

Shape* ObjectManager::getShapeById(size_t id) const
{
	Shape* shape = nullptr;
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->getShapeId() == id)
			shape = shapes[i];
	}

	return shape;
}

ObjectManager::~ObjectManager()
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
}
