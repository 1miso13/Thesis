#pragma once
#include "Shape3D.h"
class Cylinder :
	public Shape3D
{
public:
	float radius;
	float width;
	[[deprecated]]
	Cylinder();
	~Cylinder();

	void CalculateVolume();
	void CalculateSurfaceArea();
};

