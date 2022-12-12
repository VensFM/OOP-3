#include "Shape.h"

std::ostream& operator << (std::ostream& stream, const Shape& shape)
{
	rectangle_t buf = shape.getFrameRect();
	stream << shape.getName() << "  Area: " << std::round(shape.getArea());
	stream << "  Left bottom point: (" << std::round((buf.pos.x - 0.5 * buf.width)*10)/10 << ", " << std::round((buf.pos.y - 0.5 * buf.height)*10)/10;
	stream << ")  Right top point: (" << std::round((buf.pos.x + 0.5 * buf.width)*10)/10 << ", " << std::round((buf.pos.y + 0.5 * buf.height)*10)/10<<")\n";
	return stream;
}

bool Shape::operator < (const Shape& shape)
{
	return this->getArea() < shape.getArea();
}