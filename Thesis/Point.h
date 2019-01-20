#pragma once
#ifndef POINT_CLASS
#define POINT_CLASS
#include "GeometricObject.h"
#include "Vector.h"
class Point :
	public GeometricObject
{
public:
	//Parameters
	Vector3 Position;

	//functions
	Point();
	Point(float X, float Y, float Z);
	Point(Vector3 pos);
	~Point() {

	}

	Vector3 GetPosition();




	inline void operator -=(Point& A) {
		this->Position = this->Position - A.Position;
	}
	  
	  
	Point operator =(Vector3 vec) {
		Point a(vec.X, vec.Y, vec.Z);
		return a;
	}
	Point operator =(Vector2 vec) {
		return Point(vec.X, vec.Y, 0);
	}
};
/*inline Point operator *(float A, Vector3 B) {
	float X = A * B.X;
	float Y = A * B.Y;
	float Z = A * B.Z;
	return Point(X, Y, Z);
}*//*
inline Point operator *(float A, Point B) {
	float X = A * B.Position.X;
	float Y = A * B.Position.Y;
	float Z = A * B.Position.Z;
	return Point(X, Y, Z);
}*/
inline Vector3 operator -(Point A, Point B) {
	return Vector3(A.Position - B.Position);
}
inline Point operator +(Point A, Point B) {
	float X = A.Position.X + B.Position.X;
	float Y = A.Position.Y + B.Position.Y;
	float Z = A.Position.Z + B.Position.Z;
	return Point(X, Y, Z);
}
inline Point operator /(Point A, float B) {
	float X = A.Position.X / B;
	float Y = A.Position.Y / B;
	float Z = A.Position.Z / B;
	return Point(X, Y, Z);
}
inline Point operator *(Point A, float B) {
	float X = A.Position.X * B;
	float Y = A.Position.Y * B;
	float Z = A.Position.Z * B;
	return Point(X, Y, Z);
}
inline Point operator *(float B, Point A) {
	float X = A.Position.X * B;
	float Y = A.Position.Y * B;
	float Z = A.Position.Z * B;
	return Point(X, Y, Z);
}
inline Point::Point()
{
	Position = Vector3(0, 0, 0);
	GeometricType = POINTObjectType;
}

inline Point::Point(float X, float Y, float Z)
{
	Position = Vector3(X, Y, Z);
	GeometricType = POINTObjectType;
}

inline Point::Point(Vector3 pos)
{
	Position = pos;
	GeometricType = POINTObjectType;
}



inline Vector3 Point::GetPosition()
{
	return Position;
}


#endif