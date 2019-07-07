#pragma once
#include "Surface.h"

namespace Object{
class Rectangle:
	public Surface
{
public:
	float height;
	float width;
	Vector3 planeVector;
	Rectangle(
		float height,
		float width,
		Vector3 planeVector,
		Point center,
		Vector3 normal);
	~Rectangle();

	void CalculatePerimeter();
	void CalculateArea();
private:
	void createMesh();
};



}