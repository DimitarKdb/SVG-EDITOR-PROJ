#pragma once
#include "Shape.h"


class Group : public Shape {
public:

	Group();

	~Group() = default;

	void extract(size_t id);

public:

	virtual void printShapeData() const override;

	virtual void translate(const Point& vec) override;

	virtual void scale(double wCoeff, double hCoeff) override;

	virtual bool isInRegion(Point TL, Point BR) const override;

	virtual string serialize() override;

	virtual Shape* clone() override;

	virtual void insertIn(Shape* const shapePtr) override;

	virtual void ungroup(int id = -1) override;

	virtual void changeVisibility() override;

private:

	vector<Shape*> shapes;

private:

	Group(const Group& other) = delete;

	Group& operator=(const Group& other) = delete;
};
