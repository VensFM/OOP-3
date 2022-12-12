#include "Shape.h"
#include "Rectangle.h"
#include "Rectapezium.h"
#include "CompositeShape.h"
#include <fstream> 

const std::string error_open = ", not open";
const std::string composite_end_enter = ", end of composite figure not found";
const int N = 20;

void fixString(std::string& str);
void reloadStream(std::istream& stream);
void failEnter(std::istream& stream);
void failEnterForComposite(std::istream& stream);
bool getDouble(std::istream& stream, double&  x);
bool getPoint(std::istream& stream, point_t&  x);
Shape* getRectangle(std::istream& stream);
Shape* getRectapezium(std::istream& stream);
Shape* getComposite(std::istream& stream);
void sort(const int& size, Shape** ptr);
void printComposite(const int& size, Shape** ptr);

int main()
{
	int i = 0;
	std::string shape;
	std::string inFileName = "";
	std::ifstream in;
	Shape* arr[N] = {NULL};
	std::cout << "	OOP-3\n";
	try
	{
		std::cout << " Enter file to read: ";
		std::cin >> inFileName;
		in.open(inFileName);
		if (!in)
		{
			throw inFileName + error_open;
		}
		while (!in.eof())
		{
			getline(in, shape, ' ');
			fixString(shape);
			if (shape == "RECTANGLE")
			{
				arr[i]=getRectangle(in);
				if (arr[i] != NULL)
				{
					++i;
				}
			}
			else if (shape == "RECTAPEZIUM")
			{
				arr[i] = getRectapezium(in);
				if (arr[i] != NULL)
				{
					++i;
				}
			}
			else if (shape == "COMPLEX")
			{
				arr[i] = getComposite(in);
				if (arr[i] != NULL)
				{
					++i;
				}
			}
			else
			{
				failEnter(in);
			}
		}
	}
	catch (const std::string& error)
	{
		std::cerr << "Error: fail " << error << "\n";
		return -1;
	}
	in.close();
	return 0;
} 

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

Shape* getRectangle(std::istream& stream)
{
	point_t p1, p2;
	if (!getPoint(stream, p1))
	{
		failEnter(stream);
		return NULL;
	}
	if (!getPoint(stream, p2))
	{
		failEnter(stream);
		return NULL;
	}
	if (stream.peek() != '\n')
	{
		failEnter(stream);
		return NULL;
	}
	stream.ignore();
	Rectangle rect(p1, p2);
	rect.cleanValue(1);
	if (rect.checkRectangle())
	{
		return rect.clone();
	}
	return NULL;
}

Shape* getRectapezium(std::istream& stream)
{
	point_t p;
	double lowerBase, upperBase, height;
	if (!getPoint(stream, p))
	{
		failEnter(stream);
		return NULL;
	}
	if (!getDouble(stream, lowerBase))
	{
		failEnter(stream);
		return NULL;
	}
	if (!getDouble(stream, upperBase))
	{
		failEnter(stream);
		return NULL;
	}
	if (!getDouble(stream, height))
	{
		failEnter(stream);
		return NULL;
	}
	if (stream.peek() != '\n')
	{
		failEnter(stream);
		return NULL;
	}
	stream.ignore();
	Rectapezium rect(p, lowerBase, upperBase, height);
	rect.cleanValue(1);
	if (rect.checkRectapezium())
	{
		return rect.clone();
	}
	return NULL;
}

Shape* getComposite(std::istream& stream)
{
	std::string buf;
	int count, k = 0;
	bool helper = false;
	stream >> count;
	if (stream.fail() || stream.peek() != '\n')
	{
		reloadStream(stream);
		failEnterForComposite(stream);
		return NULL;
	}
	stream.ignore();
	CompositeShape composite(count);
	for (int j = 0; j < count; ++j)
	{
		getline(stream, buf, ' ');
		fixString(buf);
		if (buf == "")
		{
			stream.ignore();
			--j;
			continue;
		}
		if (buf == "RECTANGLE")
		{
			composite.add(k, getRectangle(stream));
			if (!composite.isEmpty(k))
			{
				++k;
			}
		}
		else if (buf == "RECTAPEZIUM")
		{
			composite.add(k, getRectapezium(stream));
			if (!composite.isEmpty(k))
			{
				++k;
			}
		}
		else if (buf == "COMPLEX")
		{
			composite.add(k, getComposite(stream));
			if (!composite.isEmpty(k))
			{
				++k;
			}
		}
		else if (buf == "COMPLEXEND")
		{
			helper = true;
			break;
		}
		else
		{
			failEnter(stream);
		}
	}
	if (helper != true)
	{
		getline(stream, buf, '\n');
		fixString(buf);
	}
	if (buf != "COMPLEXEND")
	{
		failEnterForComposite(stream);
		return NULL;
	}
	if (!composite.isEmpty(0))
	{
		return composite.clone();
	}
	return NULL;
}

void sort(const int& size, Shape** ptr)
{
	Shape* buf;
	for (int i = 0; i < size-1; ++i)
	{
		for (int j = size - 1; j > i; --j)
		{
			if (ptr[j] < ptr[j - 1])
			{
				buf = ptr[j];
				ptr[j] = ptr[j-1];
				ptr[j - 1] = buf;
			}
		}
	}
}

void printComposite(const int& size, Shape** ptr)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << i + 1 << ") "<<ptr[i]<<"\n";
	}
}