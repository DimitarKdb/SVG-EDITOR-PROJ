#include "Shape.h"
#include "ShapeFactory.h"

size_t Shape::objectID = 1;

Shape::Shape(const ShapeTypes type)
	:type(type)
{
	this->id = objectID++;
}

Shape::Shape(const Shape& other)
{
	this->id = objectID++;

	this->groupId = other.groupId;
	this->fill = other.fill;
	this->stroke = other.stroke;
	this->hidden = other.hidden;
}

void Shape::setGroupId(int id)
{
	groupId = id;
}

ShapeTypes Shape::getType() const
{
	return type;
}

string Shape::getTypeAsStr() const
{
	switch (type)
	{
	case ShapeTypes::ARC:
		return "Arc";
		break;
	case ShapeTypes::LINE:
		return "Line";
		break;
	case ShapeTypes::POLYGON:
		return "Polygon";
		break;
	case ShapeTypes::RECTANGLE:
		return "Rectangle";
		break;
	case ShapeTypes::GROUP:
		return "Group";
		break;
	case ShapeTypes::TRIANGLE:
		return "Triangle";
		break; 
	case ShapeTypes::ELLIPSE:
		return "Ellipse";
	default:
		return "INVALID";
		break;
	}
}

void Shape::insertIn(Shape* const shapePtr)
{
	return;
}

void Shape::ungroup(int id)
{
	return;
}

ShapeCreator::ShapeCreator(string shape) : shapeName(shape)
{
	ShapeFactory::getInstance().registerShape(this);
}
