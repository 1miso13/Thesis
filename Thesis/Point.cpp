#include "Point.h"
#include "pch.h"


Point::Point()
{
	Position = Vector3(0,0,0);
}

Point::Point(float X, float Y, float Z)
{
	Position = Vector3(X,Y,Z);
}

Point::Point(Vector3 pos)
{
	Position = pos;
}



Point::~Point()
{
}


Vector3 Point::GetPosition()
{
	return Position;
}
