#pragma once
#include "pch.h"
class Circle :
	public Surface
{
public:
	float radius;
	Circle();//TEMP TODO
	Circle(Point center, float radius, Vector3 normal) {
		this->center = center.Position;
		this->radius = radius;
		this->normal = normal;
	}
	~Circle();
};

