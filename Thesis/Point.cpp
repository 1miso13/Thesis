
#include "pch.h"
#include "Point.h"
namespace Object {

	Point::Point()
	{
		Position = Vector3(0, 0, 0);
		GeometricType = POINTObjectType;
	}

	Point::Point(float X, float Y, float Z)
	{
		Position = Vector3(X, Y, Z);
		GeometricType = POINTObjectType;
	}

	Point::Point(Vector3 pos)
	{
		Position = pos;
		GeometricType = POINTObjectType;
	}

	 Vector3 Point::GetPosition()
	{
		return Position;
	}
}