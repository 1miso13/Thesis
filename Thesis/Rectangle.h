#pragma once
#include "Surface.h"

namespace Object{
class Rectangle:
	public Surface
{
public:
	float sizeX;
	float sizeY;
	Vector3 planeVector;
	Rectangle(
		float sizeX,
		float sizeY,
		Vector3 planeVector,
		Point center,
		Vector3 normal);
	~Rectangle();

	void CalculatePerimeter();
	void CalculateArea();
};



}