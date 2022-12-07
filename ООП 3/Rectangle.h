#pragma once
#include "Shape.h"

class Rectangle :public Shape
{
public:
	Rectangle();
	Rectangle(const double& p1x, const double& p1y, const double& p2x, const double& p2y);
	Rectangle(const point_t& p1, const point_t& p2);
	Rectangle(const Rectangle& rect);

	void setP1(const point_t& p1);
	void setP1(const double& x, const double& y);
	void setP2(const point_t& p2);
	void setP2(const double& x, const double& y);
	
	point_t getP1()const;
	point_t getP2()const;

	void print()const;
	std::string getName()const override;
	double getArea()const override;
	rectangle_t getFrameRect()const override;
	void move(const point_t&  newPos)override;
	void move(const double& moveX, const double& moveY)override;
	void scale(const double& k)override;
	void scale(const point_t& p, const double& k)override;
	Shape* clone()const override;
private:
	point_t p1_;
	point_t p2_;

	point_t getCenter()const;
	void checkRectangle()const;
};