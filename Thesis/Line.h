#pragma once
#ifndef LINE_CLASS
#define LINE_CLASS
#include "pch.h"
class Line :
	public GeometricObject
{
public:
	Point beginPoint;
	Point endPoint;

	Line(Point beginPoint, Point endPoint);
	Line(Vector3 beginPoint, Vector3 endPoint);
	Line(Vector2 beginPoint, Vector2 endPoint);
	Line(Vector3 point);
	Line();
	~Line();
	Vector3 Normal();
	double Distance();
	Vector3 Middle();
};

#endif