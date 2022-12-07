#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "base-types.h"

class Shape
{
public:
	virtual ~Shape() = default;
	virtual std::string getName()const = 0;
	virtual double getArea()const = 0;
	virtual rectangle_t getFrameRect()const = 0;
	virtual void move(const point_t& newPos) = 0;
	virtual void move(const double& moveX, const double& moveY) = 0;
	virtual void scale(const double& k) = 0;
	virtual void scale(const point_t& p, const double& k) = 0;
	virtual Shape* clone()const = 0;
	friend std::ostream& operator << (std::ostream& stream, const Shape* shape);
};
