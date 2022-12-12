#include "CompositeShape.h"

CompositeShape::CompositeShape() : ptr_(nullptr), size_(0) {}
CompositeShape::CompositeShape(const int& size) : size_(size), ptr_(new Shape* [size] {nullptr}) {}
CompositeShape::CompositeShape(const CompositeShape& cShape)
{
	this->size_ = cShape.size_;
	this->ptr_ = new Shape * [size_];
	for (int i = 0; i < size_; ++i)
	{
		this->ptr_[i] = cShape.ptr_[i];
	}
}
//CompositeShape::CompositeShape(CompositeShape&& cShape)
//{
//	this->size_ = cShape.size_;
//	this->ptr_ = cShape.ptr_;
//	cShape.size_ = 0;
//	cShape.ptr_ = nullptr;
//}
CompositeShape::CompositeShape(const CompositeShape* cShape)
{
	this->size_ = cShape->size_;
	this->ptr_ = new Shape * [size_];
	for (int i = 0; i < size_; ++i)
	{
		this->ptr_[i] = cShape->ptr_[i];
	}
}
CompositeShape::~CompositeShape()
{
	if (ptr_ != nullptr)
	{
		for (int i = 0; i < size_; ++i)
		{
			delete ptr_[i];
		}
		delete[] ptr_;
	}
}

void CompositeShape::add(const int& i, Shape* newShape)
{
	ptr_[i] = newShape;
}

void CompositeShape::print()const
{
	std::cout << this;
}

bool CompositeShape::isEmpty(const int k)const
{
	if (ptr_[k] == NULL)
	{
		return true;
	}
	return false;
}

void CompositeShape::sort()
{
	Shape* buf;
	for (int i = 0; i < size_ - 1; ++i)
	{
		for (int j = size_ - 1; j > i; --j)
		{
			if (ptr_[j] < ptr_[j - 1])
			{
				buf = ptr_[j];
				ptr_[j] = ptr_[j - 1];
				ptr_[j - 1] = buf;
			}
		}
	}
}

std::string CompositeShape::getName()const
{
	return "COMPOSITE SHAPE";
}

double CompositeShape::getArea()const
{
	double area = 0;
	for (int i = 0; i < size_; i++)
	{
		area += ptr_[i]->getArea();
	}
	return area;
}

rectangle_t CompositeShape::getFrameRect()const
{
	rectangle_t shapeRect = ptr_[0]->getFrameRect();
	if (size_ < 1)
	{
		return shapeRect;
	}
	point_t pos = shapeRect.pos;
	double height = shapeRect.height,
		width = shapeRect.width,
		right = pos.x + 0.5 * width,
		left = pos.x - 0.5 * width,
		top = pos.y + 0.5 * height,
		bottom = pos.y - 0.5 * height;
	for (int i = 1; i < size_; i++)
	{
		shapeRect = ptr_[i]->getFrameRect();
		if ( right < shapeRect.pos.x + shapeRect.width * 0.5)
		{
			right = shapeRect.pos.x + shapeRect.width * 0.5;
		}
		if (left > shapeRect.pos.x - shapeRect.width * 0.5)
		{
			left = shapeRect.pos.x - shapeRect.width * 0.5;
		}
		if (top < shapeRect.pos.y + shapeRect.height * 0.5)
		{
			top = shapeRect.pos.y + shapeRect.height * 0.5;
		}
		if (bottom > shapeRect.pos.y - shapeRect.height * 0.5)
		{
			bottom = shapeRect.pos.y - shapeRect.height * 0.5;
		}
	}
	width = right - left;
	height = top - bottom;
	pos.x = width * 0.5;
	pos.y = height * 0.5;
	return { width, height, pos };
}

void CompositeShape::move(const point_t& pos)
{
	point_t lastPos = getFrameRect().pos;
	move(lastPos.x - pos.x, lastPos.y - pos.y);
}

void CompositeShape::move(const double& x, const double& y)
{
	for (int i = 0; i < size_; i++)
	{
		ptr_[i]->move(x, y);
	}
}

void CompositeShape::scale(const double& k)
{
	if (k <= 0)
	{
		std::cerr << "\n	Invalid coef\n";
		return;
	}
	point_t pos = getFrameRect().pos;
	for (int i = 0; i < size_; ++i)
	{
		point_t shapePos = ptr_[i]->getFrameRect().pos;
		double moveX = pos.x + (shapePos.x - pos.x) * k;
		double moveY = pos.y + (shapePos.y - pos.y) * k;
		ptr_[i]->move(moveX, moveY);
		ptr_[i]->scale(k);
	}
}

void CompositeShape::scale(const point_t& p, const double& k)
{
	if (k <= 0)
	{
		std::cerr << "\n	Invalid coef\n";
		return;
	}
	for (int i = 0; i < size_; ++i)
	{
		point_t shapePos = ptr_[i]->getFrameRect().pos;
		double moveX = p.x + (shapePos.x - p.x) * k;
		double moveY = p.y + (shapePos.y - p.y) * k;
		ptr_[i]->move(moveX, moveY);
		ptr_[i]->scale(k);
	}
}

Shape* CompositeShape::clone()const
{
	return new CompositeShape(this);
}