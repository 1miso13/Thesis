#pragma once
#include "Shape3D.h"
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
	Pyramid(Point apex, Surface* base, short BaseType);
	Pyramid(float height, Surface* base, short BaseType);
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

};

