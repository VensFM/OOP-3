#include "Shape.h"

std::ostream& operator << (std::ostream& stream, const Shape* shape)
{
	point_t buf = shape->getFrameRect().pos;
	double height = shape->getFrameRect().height;
	double width = shape->getFrameRect().width;
	stream << shape->getName() << "  Area: " << std::round(shape->getArea());
	stream << "  Left bottom point: (" << std::round((buf.x - 0.5 * width)*10)/10 << ", " << std::round((buf.y - 0.5 * height)*10)/10;
	stream << ")  Right top point: (" << std::round((buf.x + 0.5 * width)*10)/10 << ", " << std::round((buf.y + 0.5 * height)*10)/10<<")\n";
	return stream;
}

bool Shape::operator < (const Shape* shape)
{
	return this->getArea() < shape->getArea();
}