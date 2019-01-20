#pragma once
#include "Point.h"
#include "Shape3D.h"
#include "Surface.h"
#include "Line.h"
#include "Triangle.h"
#include "Circle.h"
class Pyramid :
	public Shape3D
{
public:
	/// <summary>
	/// 1-circle
	/// 2-triangle
	/// 3-rectangle
	/// 4-polygon
	/// </summary>
	short BaseType;

	Point apex;
	Surface *base;
	float height;
	Pyramid(Point apex, Surface* base);
	Pyramid(float height, Surface* base);
	~Pyramid();

	void CalculateHeight();

	/// <summary>
	/// only with height
	/// </summary>
	void CalculateVolume();
	/// <summary>
	/// only with height
	/// </summary>
	void CalculateSurfaceArea();

	short GetBaseType();
};

