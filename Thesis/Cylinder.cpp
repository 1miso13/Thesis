#include "pch.h"
#include "Cylinder.h"

Cylinder::Cylinder()
{
	GeometricType = CYLINDER;
}


Cylinder::~Cylinder()
{
}

void Cylinder::CalculateVolume()
{
	volume = (4. * atan(1.)) * radius * radius * width;
}

void Cylinder::CalculateSurfaceArea()
{
	double perimeterBase = 2 * (4. * atan(1.))/*PI*/ * radius;
	double areaBase = (4. * atan(1.)) * radius * radius;
	surfaceArea = areaBase * 2 + perimeterBase * width;
}
