#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
	CompositeShape();
	CompositeShape(const int& size);
	~CompositeShape();

	std::string getName()const;
private:
	int size_;
	Shape** ptr_;
};