#include "Rectapezium.h"

Rectapezium::Rectapezium() : 
	pos_(), 
	lowerBase_(0.0), 
	upperBase_(0.0), 
	height_(0.0) {}
Rectapezium::Rectapezium(const double& x, const double& y, const double& lowerBase, const double& upperBase, const double& height) : 
	pos_(x, y), 
	lowerBase_(lowerBase), 
	upperBase_(upperBase), 
	height_(height) 
{ checkRectapezium(); }
Rectapezium::Rectapezium(const point_t& p, const double& lowerBase, const double& upperBase, const double& height) :
	pos_(p),
	lowerBase_(lowerBase),
	upperBase_(upperBase),
	height_(height)
{ checkRectapezium(); }
Rectapezium::Rectapezium(const Rectapezium& rect) :
	pos_(rect.pos_),
	lowerBase_(rect.lowerBase_),
	upperBase_(rect.upperBase_),
	height_(rect.height_) {}

void Rectapezium::setPos(const point_t& p)
{
	pos_.x = p.x;
	pos_.y = p.y;
}

void Rectapezium::setPos(const double& x, const double& y)
{
	pos_.x = x;
	pos_.y = y;
}

void Rectapezium::setLowerBase(const double& lowerBase)
{
	lowerBase_ = lowerBase;
	checkRectapezium();
}

void Rectapezium::setUpperBase(const double& upperBase)
{
	upperBase_ = upperBase;
	checkRectapezium();
}

void Rectapezium::setHeight(const double& height)
{
	height_ = height;
	checkRectapezium();
}

point_t Rectapezium::getPos()const
{
	return pos_;
}

double Rectapezium::getLowerBase()const
{
	return lowerBase_;
}

double Rectapezium::getUpperBase()const
{
	return upperBase_;
}

double Rectapezium::getHeight()const
{
	return height_;
}

std::string Rectapezium::getName()
{
	return "RECTAPEZIUM";
}

double Rectapezium::getArea()const
{
	return 0.5 * height_ * (lowerBase_ + upperBase_);
}

rectangle_t Rectapezium::getFrameRect()const
{
	int flagBase = 0,
		flagHeight = 0;
	if (lowerBase_ > 0)
	{
		flagBase = 1;
	}
	else
	{
		flagBase = -1;
	}
	if (height_ > 0)
	{
		flagHeight = 1;
	}
	else
	{
		flagHeight = -1;
	}
	if (std::abs(lowerBase_) > std::abs(upperBase_))
	{
		return{ std::abs(lowerBase_), std::abs(height_), {pos_.x + 0.5 * lowerBase_ * flagBase, pos_.y + 0.5 * height_ * flagHeight } };
	}
	else
	{
		return{ std::abs(upperBase_), std::abs(height_), {pos_.x + 0.5 * upperBase_ * flagBase, pos_.y + 0.5 * height_ * flagHeight } };
	}
}

void Rectapezium::move(const point_t& newPos)
{
	pos_.x = newPos.x;
	pos_.y = newPos.y;
}

void Rectapezium::move(const double& moveX, const double& moveY)
{
	pos_.x += moveX;
	pos_.y += moveY;
}

void Rectapezium::scale(const double& k)
{
	if (k == 0)
	{
		std::cerr << "\n	Invalid coef" << std::endl;
		return;
	}
	point_t buf = getCenter();
	pos_.x = buf.x - ((buf.x - pos_.x) * k);
	pos_.y = buf.y - ((buf.y - pos_.y) * k);
	lowerBase_ *= k;
	upperBase_ *= k;
	height_ *= k;
}

void Rectapezium::scale(const point_t& p, const double& k)
{
	if (k <= 0)
	{
		std::cerr << "\n	Invalid coef" << std::endl;
		return;
	}
	point_t buf = getCenter();
	double moveX = p.x + (buf.x - p.x) * k;
	double moveY = p.y + (buf.y - p.y) * k;
	this->move(moveX, moveY);
	this->scale(k);
}

Shape* Rectapezium::clone()const
{
	Shape* ptr = new Rectapezium(this->pos_, this->lowerBase_, this->upperBase_, this->height_);
	return ptr;
}

point_t Rectapezium::getCenter()const
{
	return { pos_.x + (0.25 * (lowerBase_ + upperBase_)), pos_.y + (0.5 * height_) };
}

void Rectapezium::checkRectapezium()const
{
	if (lowerBase_ == 0 || upperBase_ == 0 || height_ == 0)
	{
		std::cerr << "\n	Invalid data, last three values can't be zero: " << this << std::endl;
		return;
	}
	if ((lowerBase_ < 0 && upperBase_ > 0) || (lowerBase_ > 0 && upperBase_ < 0))
	{
		std::cerr << "\n	Invalid data, upperBase and lowerBase must be of the same character: " << this << std::endl;
		return;
	}
}