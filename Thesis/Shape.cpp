#include "pch.h"



Shape::Shape(std::vector<Point> pointsVector)
{
	this->pointsVector = pointsVector;
	this->center = pointsVector[0].Position;

	this->normal = crossProduct3Points(pointsVector[0].Position, pointsVector[1].Position, pointsVector[2].Position).Normalize();
}


Shape::~Shape()
{
}
