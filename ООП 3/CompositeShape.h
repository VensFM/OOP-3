#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
	CompositeShape();
	CompositeShape(const int& size);
	~CompositeShape();
private:
	int size_;
	Shape** ptr_;
};