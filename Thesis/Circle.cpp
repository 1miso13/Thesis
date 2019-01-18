#include "pch.h"
#include "Circle.h"

void Circle::CalculatePerimeter()
{
	perimeter = 2* (4. * atan(1.))/*PI*/ * radius;
}

void Circle::CalculateArea()
{
	area = (4. * atan(1.)) * radius * radius;
}


Circle::~Circle()
{
}
