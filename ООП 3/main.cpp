#include <fstream> 
#include "Shape.h"
#include "utils.h"
#include "Rectangle.h"
#include "Rectapezium.h"
#include "CompositeShape.h"

const std::string error_open = ", not open";
const std::string invalid_test_conctructor = ", composite shape not found";
const int N = 20;

Shape* getRectangle(std::istream& stream);
Shape* getRectapezium(std::istream& stream);
Shape* getComposite(std::istream& stream);
void sort(const int& size, Shape** ptr);
void printArray(const int& size, Shape** ptr);

int main()
{
	point_t bufP;
	double bufD;
	int i = 0, k = N + 1;
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
			in >> shape;
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
			else if (shape == "MOVE")
			{
				if (!getPoint(in, bufP))
				{
					failEnter(in);
					continue;
				}
				system("cls");
				std::cout << "	OOP-3 Test move...\n\n Shapes befor moving: \n";
				printArray(i, arr);
				for (int j = 0; j < i; ++j)
				{
					arr[j]->move(bufP.x, bufP.y);
				}
				std::cout << " Shapes after moving along the abscissa and ordinate axes x = "<<bufP.x<<", y = "<<bufP.y<<" : \n";
				printArray(i, arr);
				for (int j = 0; j < i; ++j)
				{
					arr[j]->move(bufP);
				}
				std::cout << " Shapes after moving to a specific point (" << bufP.x << ", " << bufP.y << ") : \n";
				printArray(i, arr);
				system("pause");
				system("cls");
			}
			else if (shape == "SCALE")
			{
				if (!getPoint(in, bufP))
				{
					failEnter(in);
					continue;
				}
				if (!getDouble(in, bufD))
				{
					failEnter(in);
					continue;
				}
				system("cls");
				std::cout << "	OOP-3 Test scale...\n\n Shapes befor scaling: \n";
				printArray(i, arr);
				for (int j = 0; j < i; ++j)
				{
					arr[j]->scale(bufP, bufD);
				}
				std::cout << " Shapes after isotropic scaling, point ("<<bufP.x<<", "<<bufP.y<<") coef = " << bufD <<" : \n";
				printArray(i, arr);
				system("pause");
				system("cls");
			}
			else
			{
				failEnter(in);
			}
		}
		system("cls");
		std::cout << "	OOP-3 Test sort...\n\n Shapes befor sorting: \n";
		printArray(i, arr);
		sort(i, arr);
		std::cout << " Shapes after sorting: \n";
		printArray(i, arr);
		system("pause");
		system("cls");
		std::cout << "	OOP-3 Test move constructor...\n\n";
		CompositeShape ex1(i);
		for (int j = 0; j < i; ++j)
		{
			ex1.add(j, arr[j]);
		}
		std::cout << " Shapes befor move constructor: \n1) "<<ex1<<"\n2) Not yet announced\n\n";
		CompositeShape ex2 = std::move(ex1);
		std::cout << " Shapes after move constructor: \n1) "<< ex1<<"\n2) "<<ex2<<"\n";
		system("pause");
		system("cls");
	}
	catch (const std::string& error)
	{
		std::cerr << "Error: fail " << error << "\n";
		return -1;
	}
	in.close();
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
		stream>>buf;
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
		stream >> buf;
	}
	if (buf != "COMPLEXEND")
	{
		failEnterForComposite(stream);
		return NULL;
	}
	composite.setSize(k);
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
			if (ptr[j]->getArea() < ptr[j - 1]->getArea())
			{
				buf = ptr[j];
				ptr[j] = ptr[j-1];
				ptr[j - 1] = buf;
			}
		}
	}
}

void printArray(const int& size, Shape** ptr)
{
	for (int i = 0; i < size; ++i)
	{
		std::cout <<"	"<< i + 1 << ") "<<*ptr[i]<<"\n";
	}
}