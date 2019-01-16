#include "pch.h"



Polygon::Polygon(std::vector<Point> pointsVector)
{
	this->pointsVector = pointsVector;
	this->center = pointsVector[0].Position;

	this->normal = crossProduct3Points(pointsVector[0].Position, pointsVector[1].Position, pointsVector[2].Position).Normalize();
}


Polygon::~Polygon()
{
}
