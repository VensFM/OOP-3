#include "CompositeShape.h"

CompositeShape::CompositeShape() : ptr_(nullptr), size_(0) {}
CompositeShape::CompositeShape(const int& size) : size_(size-1), ptr_(new Shape*[size_]) {}
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

std::string CompositeShape::getName()const
{
	return "COMPOSITE SHAPE";
}