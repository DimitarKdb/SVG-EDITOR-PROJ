#pragma once
#include "Shape.h"
#include <vector>
#include <fstream>

using std::vector;
using std::ofstream;

class ObjectManager
{
public:

	static ObjectManager& getInstance();

	bool createShape(const string& shapeType, vector<string>& shapeParameters);

	bool readShapes(const string& fileName);

	bool translateShape(int id, Point vec);

	bool translateAll(Point vec);

	bool scaleShape(size_t id, double wCoeff, double hCoeff);

	bool scaleAll(double wCoeff, double hCoeff);

	bool saveAs(const string& fileName);

	void print();

	bool showFigure(int id);

	bool hideFigure(int id);

	bool group(Point TL, Point BR);

	bool ungroup(size_t id);

	bool insert(size_t grId, size_t shapeId);

	bool extract(size_t grId, size_t shapeId);

	bool stroke(size_t shapeId, const string& newStrokeColor);

	bool fill(size_t shapeId, const string& newFillColor);

private:

	vector<Shape*> shapes;

private:

	bool readFile(const string& fileName, bool(*lineConstraints)(const string& fileName));

	bool readSVG(const string& fileName);

	bool readTXT(const string& fileName);

	void saveToFile(ofstream& outputFile);

	bool saveSVG(const string& fileName);

	bool saveTXT(const string& fileName);

	string getExtension(const string& fileName);

	Shape* getShapeById(size_t id) const;

private:

	ObjectManager() = default;

	ObjectManager(const ObjectManager& other) = delete;

	ObjectManager& operator=(const ObjectManager& other) = delete;

	~ObjectManager();
};

