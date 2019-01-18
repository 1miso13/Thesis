#pragma once
#include "pch.h"
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
	}
	~Rectangle();

	void CalculatePerimeter();
	void CalculateArea();
};

