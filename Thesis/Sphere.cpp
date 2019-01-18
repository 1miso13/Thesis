#include "pch.h"
#include "Sphere.h"


Sphere::Sphere(Point center, float radius)
{
	this->center = center;
	this->radius = radius;
	GeometricType = SPHERE;
}


Sphere::~Sphere()
{
}

void Sphere::CalculateVolume()
{

	volume = (4. * atan(1.) * radius * radius * radius * 4) / 3;
}

void Sphere::CalculateSurfaceArea()
{
	surfaceArea = 4 * 4. * atan(1.) * radius * radius;
}
