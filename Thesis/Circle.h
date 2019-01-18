#pragma once
#include "pch.h"
class Circle :
	public Surface
{
public:
	float radius;
	Circle(Point center, float radius, Vector3 normal) {
		this->center = center;
		this->radius = radius;
		this->normal = normal;
		GeometricType = CIRCLE;
	}
	~Circle();

	void CalculatePerimeter();
	void CalculateArea();
};

