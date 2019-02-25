#include "pch.h"
#include "Rectangle.h"


namespace Object {

	Rectangle::Rectangle(
		float sizeX,
		float sizeY,
		Vector3 planeVector,
		Point center,
		Vector3 normal) {
		this->center = center;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->planeVector = planeVector;
		this->normal = normal;
		GeometricType = RECTANGLE_ObjectType;
	}
	Rectangle::~Rectangle()
	{
	}

	void Rectangle::CalculatePerimeter()
	{
		perimeter = (double)sizeX + (double)sizeX + (double)sizeY + (double)sizeY;
	}

	void Rectangle::CalculateArea()
	{
		area = (double)sizeX * (double)sizeY;
	}


}