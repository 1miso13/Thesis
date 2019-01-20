#pragma once
#ifndef LINE_CLASS
#define LINE_CLASS
#include "GeometricObject.h"
#include "Point.h"
class Line :
	public GeometricObject
{
private:
	void DistanceCalc();
public:
	Point beginPoint;
	Point endPoint;
	double distance;

	Line(Point beginPoint, Point endPoint);
	Line(Vector3 beginPoint, Vector3 endPoint);
	Line(Vector2 beginPoint, Vector2 endPoint);
	Line(Vector3 point);
	Line();
	~Line();
	Vector3 Normal();
	float Distance();
	Vector3 Middle();
	Vector3 Vector();
};

#endif