#include "pch.h"

Line::Line(Point beginPoint, Point endPoint)
{
	this->beginPoint = beginPoint;
	this->endPoint = endPoint;
}

Line::Line(Vector3 beginPoint, Vector3 endPoint)
{
	this->beginPoint = beginPoint;
	this->endPoint = endPoint;
}

Line::Line(Vector2 beginPoint, Vector2 endPoint)
{
}

Line::Line(Vector3 point)
{
	this->beginPoint = Vector3(0, 0, 0);
	this->endPoint = point;
}
Line::Line()
{
	this->beginPoint = Vector3(0, 0, 0);
	this->endPoint = Vector3(0, 0, 0);
}


Line::~Line()
{
}

Vector3 Line::Normal()
{
	return  this->endPoint - this->beginPoint;
	
}


double Line::Distance()
{
	Vector3 tmp = this->endPoint - this->beginPoint;
	return tmp.Distance();
	
	//return	sqrt(tmp.X*tmp.X + tmp.Y*tmp.Y + tmp.Z*tmp.Z);
}

Vector3 Line::Middle()
{
	
	return ((this->endPoint + this->beginPoint) / 2.0f).Position;
}

