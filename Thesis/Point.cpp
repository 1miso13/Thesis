
#include "pch.h"
#include "Point.h"
namespace Object {
Point::Point()
	{
		Position = Vector3(0, 0, 0);
		GeometricType = POINT_ObjectType;
		createMesh();
	}

	Point::Point(float X, float Y, float Z)
	{
		Position = Vector3(X, Y, Z);
		GeometricType = POINT_ObjectType;
		createMesh();
	}

	Point::Point(Vector3 pos)
	{
		Position = pos;
		GeometricType = POINT_ObjectType;
		createMesh();
	}

	 Vector3 Point::GetPosition()
	{
		return Position;
	}
}