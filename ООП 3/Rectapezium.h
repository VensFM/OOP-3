#pragma once
#include "Shape.h"

class Rectapezium :public Shape
{
public:
	Rectapezium();
	Rectapezium(const double& x, const double& y, const double& lowerBase, const double& upperBase, const double& height);
	Rectapezium(const point_t& p, const double& lowerBase, const double& upperBase, const double& height);
	Rectapezium(const Rectapezium& rect);
	~Rectapezium() = default;

	void setPos(const point_t& p);
	void setPos(const double& x, const double& y);
	void setLowerBase(const double& lowerBase);
	void setUpperBase(const double& upperBase);
	void setHeight(const double& height);

	point_t getPos()const;
	double getLowerBase()const;
	double getUpperBase()const;
	double getHeight()const;

	std::string getName()override;
	double getArea()const override;
	rectangle_t getFrameRect()const override;
	void move(const point_t& newPos)override;
	void move(const double& moveX, const double& moveY)override;
	void scale(const double& k)override;
	Shape* clone()override;
private:
	point_t pos_;
	double lowerBase_;
	double upperBase_;
	double height_;

	point_t getCenter()const;
	void checkRectapezium()const;
};
