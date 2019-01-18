#include "pch.h"
#include "Rectangle.h"



Rectangle::~Rectangle()
{
}

void Rectangle::CalculatePerimeter()
{
	perimeter = sizeX + sizeX + sizeY + sizeY;
}

void Rectangle::CalculateArea()
{
	area = sizeX * sizeY;
}
