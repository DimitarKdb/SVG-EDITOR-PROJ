#include "ShapeFactory.h"
#include <iostream>

using std::cout;
using std::endl;

ShapeFactory& ShapeFactory::getInstance()
{
    static ShapeFactory factoryInstance;

    return factoryInstance;
}

void ShapeFactory::registerShape(const ShapeCreator* creator)
{
    creators.push_back(creator);
}

Shape* ShapeFactory::createShape(string& line) 
{
    string shapeName;

    for (size_t i = 1; i < line.length(); i++)
    {
        if (line[i] == ' ')
            break;

        shapeName.push_back(line[i]);
    }

    const ShapeCreator* creator = getCreator(shapeName);

    if (creator) {
        return creator->createShape(line);
    }
    else {
        std::cout << "Shape: " << shapeName << " was not recognized by the application." << endl;

        return nullptr;
    }
}

Shape* ShapeFactory::createShape(const string& shapeType, vector<string>& shapeParameters)
{
    const ShapeCreator* creator = getCreator(shapeType);

    if (creator) {
        return creator->createShape(shapeParameters);
    }
    else {
        std::cout << "Shape: " << shapeType << " was not recognized by the application." << endl;

        return nullptr;
    }
}

ShapeFactory::ShapeFactory()
{
    creators.reserve(ShapeFactory::MAX_CREATORS);
}

const ShapeCreator* ShapeFactory::getCreator(const string& str)
{
    for (size_t i = 0; i < creators.size(); i++)
    {
        if (creators[i]->getShapeName() == str) {
            return creators[i];
        }
    }

    return nullptr;
}
