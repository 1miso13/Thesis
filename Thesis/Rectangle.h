#pragma once
#include "pch.h"
class Rectangle:
	public Surface
{
public:
	float sizeX;
	float sizeY;
	float RotationAroundNormal;//[0,360]
	Rectangle() {//TEMPORAL TODO

	}
	Rectangle(
		float sizeX,
		float sizeY,
		float RotationAroundNormal/*[0,360]*/,
		Point center, 
		Vector3 normal) {
		this->center = center.Position;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->RotationAroundNormal = RotationAroundNormal;
		this->normal= normal;
	}
	~Rectangle();
};

