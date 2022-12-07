#include "Shape.h"
#include "Rectangle.h"
#include "Rectapezium.h"
#include "CompositeShape.h"
#include <fstream> 

const std::string error_open = ", not open";
const int N = 20;
std::string buf;

bool getDouble(std::istream& in, double& x);
void getRectangle(std::istream& in, int& i, Shape** arr);
void sort(const int& size, Shape** ptr);
void printComposite(const int& size, Shape** ptr);

int main()
{
	int i = 0;
	std::string shape;
	Shape* arr[N] = {nullptr};
	std::cout << "	OOP-3\n";
	std::string inFileName = "";
	std::ifstream in;
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
			while (shape != "MOVE" || shape != "SCALE")
			{
				getline(in, shape, ' ');
				if (shape == "RECTANGLE")
				{
					getRectangle(in, i, arr);
				}
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

bool getDouble(std::istream& in, double& x)
{
	in >> x;
	if (in.fail())
	{
		std::cerr << "\n	Shape is set incorrectly\n";
		return false;
	}
	return true;
}

void getRectangle(std::istream& in, int& i, Shape** arr)
{
	double p1x, p1y, p2x, p2y;
	if (!getDouble(in,p1x))
	{
		getline(in, buf, '\n');
		in.ignore();
		return;
	}
	if (!getDouble(in, p1y))
	{
		getline(in, buf, '\n');
		in.ignore();
		return;
	}
	if (!getDouble(in, p2x))
	{
		getline(in, buf, '\n');
		in.ignore();
		return;
	}
	if (!getDouble(in, p2y))
	{
		getline(in, buf, '\n');
		in.ignore();
		return;
	}
	if (in.peek() != '\n' || in.peek() != -1)
	{
		std::cerr << "\n	Shape is set incorrectly\n";
		getline(in, buf, '\n');
		in.ignore();
		return;
	}
	Rectangle rect(p1x, p1y, p2x, p2y);
	arr[i] = rect.clone();

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