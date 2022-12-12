#include "Rectangle.h"

Rectangle::Rectangle() : p1_(), p2_() {}
Rectangle::Rectangle(const double& p1x, const double& p1y, const double& p2x, const double& p2y) : p1_(p1x, p1y), p2_(p2x, p2y) {}
Rectangle::Rectangle(const point_t& p1, const point_t& p2) : p1_(p1), p2_(p2) {}
Rectangle::Rectangle(const Rectangle& rect) : p1_(rect.p1_), p2_(rect.p2_) {}

void Rectangle::setP1(const point_t& p1)
{
	p1_.x = p1.x;
	p1_.y = p1.y;
	checkRectangle();
}

void Rectangle::setP1(const double& x, const double& y)
{
	p1_.x = x;
	p1_.y = y;
	checkRectangle();
}

void Rectangle::setP2(const point_t& p2)
{
	p2_.x = p2.x;
	p2_.y = p2.y;
	checkRectangle();
}

void Rectangle::setP2(const double& x, const double& y)
{
	p2_.x = x;
	p2_.y = y;
	checkRectangle();
}

point_t Rectangle::getP1()const
{
	return p1_;
}

point_t Rectangle::getP2()const
{
	return p2_;
}

void Rectangle::cleanValue(const int k)
{
	p1_.x = std::round(p1_.x * std::pow(10, k)) / std::pow(10, k);
	p1_.y = std::round(p1_.y * std::pow(10, k)) / std::pow(10, k);
	p2_.x = std::round(p2_.x * std::pow(10, k)) / std::pow(10, k);
	p2_.y = std::round(p2_.y * std::pow(10, k)) / std::pow(10, k);
	return;
}

std::string Rectangle::getName()const
{
	return "RECTANGLE";
}

double Rectangle::getArea()const
{
	return 0.5 * std::abs(p1_.x - p2_.x) * std::abs(p1_.y - p2_.y);
}

rectangle_t Rectangle::getFrameRect()const
{
	rectangle_t buf;
	buf.height = std::abs(p1_.y - p2_.y);
	buf.width = std::abs(p1_.x - p2_.x);
	buf.pos = this->getCenter();
	return buf;
}

void Rectangle::move(const point_t& newPos)
{
	point_t buf = this->getCenter();
	buf.x -= newPos.x;
	buf.y -= newPos.y;
	p1_.x -= buf.x;
	p1_.y -= buf.y;
	p2_.x -= buf.x;
	p2_.y -= buf.y;
}

void Rectangle::move(const double& moveX, const double& moveY)
{
	p1_.x += moveX;
	p2_.x += moveX;
	p1_.y += moveY;
	p2_.y += moveY;
}

void Rectangle::scale(const double& k)
{
	if (k == 0)
	{
		std::cerr << "\n	Invalid coef\n";
		return;
	}
	point_t buf = getCenter();
	p1_.x = buf.x - ((buf.x - p1_.x) * k);
	p2_.x = buf.x - ((buf.x - p2_.x) * k);
	p1_.y = buf.y - ((buf.y - p1_.y) * k);
	p2_.y = buf.y - ((buf.y - p2_.y) * k);
}

void Rectangle::scale(const point_t& p, const double& k)
{
	if (k <= 0)
	{
		std::cerr << "\n	Invalid coef\n";
		return;
	}
	point_t buf = getCenter();
	double moveX = p.x + (buf.x - p.x) * k;
	double moveY = p.y + (buf.y - p.y) * k;
	this->move(moveX, moveY);
	this->scale(k);
}

Shape* Rectangle::clone()const 
{
	return new Rectangle(this->p1_, this->p2_);
}

bool Rectangle::checkRectangle()const
{
	if (p1_.x == p2_.x || p1_.y == p2_.y)
	{
		system("cls");
		std::cerr << "			!!!ERROR!!!\n	Invalid data, two points can't lie on the same line:\n" << *this << " \n";
		system("pause");
		system("cls");
		return 0;
	}
	return 1;
}

point_t Rectangle::getCenter()const
{
	point_t buf;
	double width = std::abs(p1_.x - p2_.x), 
		   height = std::abs(p1_.y - p2_.y);
	if (p1_.x > p2_.x)
	{
		buf.x = p1_.x - (width * 0.5);
	}
	else
	{
		buf.x = p1_.x + (width * 0.5);
	}
	if (p1_.y > p2_.y)
	{
		buf.y = p1_.y - (height * 0.5);
	}
	else
	{
		buf.y = p1_.y + (height * 0.5);
	}
	return buf;
}