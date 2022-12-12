#include "utils.h"
#include <string>
#include "base-types.h"

const std::string composite_end_enter = ", end of composite figure not found";

void fixString(std::string& str)
{
	while (str[0] == '\n')
	{
		str.erase(0, 1);
	}
	return;
}

void reloadStream(std::istream& stream)
{
	stream.clear();
	stream.sync();
	return;
}

void failEnter(std::istream& stream)
{
	std::string buf;
	getline(stream, buf, '\n');
	return;
}

void failEnterForComposite(std::istream& stream)
{
	std::string buf;
	while (buf != "COMPLEXEND")
	{
		if (stream.eof())
		{
			throw composite_end_enter;
		}
		getline(stream, buf, '\n');
	}
	return;
}

void cleanValue(double& x,int k)
{
	x = std::round(x * std::pow(10, k)) / pow(10, k);
}

bool getDouble(std::istream& stream, double& x)
{
	if (stream.peek() == '\n')
	{
		return 0;
	}
	stream >> x;
	if (stream.fail())
	{
		reloadStream(stream);
		return 0;
	}
	cleanValue(x, 1);
	return 1;
}

bool getPoint(std::istream& stream, point_t& point)
{
	if (getDouble(stream, point.x))
	{
		if (getDouble(stream, point.y))
		{
			return 1;
		}
	}
	return 0;
}