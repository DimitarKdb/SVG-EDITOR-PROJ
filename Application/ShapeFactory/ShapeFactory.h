#pragma once
#include "Shape.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class ShapeFactory
{
public:

    static ShapeFactory& getInstance();

    void registerShape(const ShapeCreator* creator);

    Shape* createShape(string& line);

    Shape* createShape(const string& shapeType, vector<string>& shapeParameters);

private:

    const ShapeCreator* getCreator(const string& str);

    ShapeFactory();

    ~ShapeFactory() = default;

    ShapeFactory(const ShapeFactory&) = delete;

    ShapeFactory& operator=(const ShapeFactory&) = delete;

private:

    constexpr static size_t MAX_CREATORS = 5;

    vector<const ShapeCreator*> creators;
};

