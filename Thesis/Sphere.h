#pragma once
#include "Shape3D.h"
class Sphere :
	public Shape3D
{
public:
	Point center;
	float radius;
	Sphere(Point center, float radius);
	~Sphere();
	void CalculateVolume();
	void CalculateSurfaceArea();
};

