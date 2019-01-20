#include "pch.h"
#include "Vector.h"
//
//Vector3 Vector3::operator=(Point p)
//{
//	return p.Position;
//}

float Vector3::Dot(Vector3 VectorA, Vector3 VectorB) {
	return VectorA.X*VectorB.X + VectorA.Y*VectorB.Y + VectorA.Z*VectorB.Z;
}
