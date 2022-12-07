#include "Shape.h"
#include "Rectangle.h"
#include "Rectapezium.h"
#include "CompositeShape.h"

void sort(const int& size, Shape** ptr);

int main()
{


	return 0;
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