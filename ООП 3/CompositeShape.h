#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
	CompositeShape();
	CompositeShape(const int& size);
	~CompositeShape();

	std::string getName()const;
	double getArea()const;
	rectangle_t getFrameRect()const;
	void move(const point_t& newPos);
	void move(const double& moveX, const double& moveY);
	void scale(const double& k);
private:
	int size_;
	Shape** ptr_;
};