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
		Vector3 normal) {
		this->center = center;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->planeVector = planeVector;
		this->normal= normal;
		GeometricType = RECTANGLE;
	}
	~Rectangle();

	void CalculatePerimeter();
	void CalculateArea();
};



inline Rectangle::~Rectangle()
{
}

inline void Rectangle::CalculatePerimeter()
{
	perimeter = (double)sizeX + (double)sizeX + (double)sizeY + (double)sizeY;
}

inline void Rectangle::CalculateArea()
{
	area = (double)sizeX * (double)sizeY;
}
}