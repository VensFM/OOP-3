#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
public:
	CompositeShape();
	CompositeShape(const int& size);
	CompositeShape(const CompositeShape& cShape);
	/*CompositeShape(CompositeShape&& cShape);*/
	CompositeShape(const CompositeShape* cShape);
	~CompositeShape();

	void add(const int& i, Shape* newShape);
	std::string getName() override;
	double getArea()const override;
	rectangle_t getFrameRect()const override;
	void move(const point_t& newPos) override;
	void move(const double& moveX, const double& moveY) override;
	void scale(const double& k) override;
	void scale(const point_t& p, const double& k)override;
	Shape* clone()const override;
private:
	int size_;
	Shape** ptr_;
};