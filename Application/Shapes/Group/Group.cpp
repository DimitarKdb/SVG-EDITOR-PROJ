#include "Group.h"
#include <iostream>

using std::cout;
using std::endl;

Group::Group()
	: Shape(ShapeTypes::GROUP)
{
	shapes.reserve(2);
}

void Group::extract(size_t id)
{
	if (id == 0)
		return;

	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->getShapeId() == id) {

			shapes[i]->changeGroupedState();
			shapes[i]->setGroupId(-1);

			for (size_t j = i; j < shapes.size() - 1; j++)
			{
				shapes[j] = shapes[j + 1];
			}

			shapes.pop_back();
			break;
		}
	}
}

void Group::ungroup(int id) 
{
	if (id == -1) {

		for (size_t i = 0; i < shapes.size(); i++)
		{
			shapes[i]->changeGroupedState();
			shapes[i]->setGroupId(-1);
			shapes[i] = nullptr;
		}
	}
	else {
		extract(id);
	}

}

void Group::changeVisibility()
{
	this->hidden = !hidden;

	for (size_t i = 0; i < shapes.size(); i++)
	{
		shapes[i]->changeVisibility();
	}
}

void Group::printShapeData() const
{
	cout << "This is a group with id: " << this->id << ", which consists of : " << shapes.size() << " shapes." << endl;
	for (size_t i = 0; i < shapes.size(); i++)
	{
		cout << "  --- Shape: " << shapes[i]->getTypeAsStr() << " - ID: " << shapes[i]->getShapeId() << "." << endl;
	}
}

void Group::translate(const Point& vec)
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		shapes[i]->translate(vec);
	}
}

void Group::scale(double wCoeff, double hCoeff)
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		shapes[i]->scale(wCoeff, hCoeff);
	}
}

bool Group::isInRegion(Point TL, Point BR) const
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (!shapes[i]->isInRegion(TL, BR))
			return false;
	}


	return true;
}

string Group::serialize()
{
	return "";
}

Shape* Group::clone()
{
	return this;
}

void Group::insertIn(Shape* const shapePtr)
{
	shapes.push_back(shapePtr);
	shapePtr->setGroupId(this->id);
	shapePtr->changeGroupedState();
}
