#pragma once
#include "pch.h"
#include <vector>
#include "Vector.h"
#include "Point.h"
#include "Matrix.h"

Vector3 crossProduct2Vectors(Vector3 VectorA, Vector3 VectorB);

Vector3 crossProduct3Points(Vector3 *arrayOfPoints);

Vector3 crossProduct3Points(Vector3 p1, Vector3 p2, Vector3 p3);

float DotProduct(Vector3 VectorA, Vector3 VectorB);

void Plane3DTo2D(Vector3 * arrayOfPoints, unsigned int pointsCount, Vector3 * normal);
void Plane3DTo2D(Vector3 * arrayOfPoints, unsigned int pointsCount, Vector3 * normal, Vector3 origin);
void Plane2DTo3D(Vector3 * arrayOfPoints, unsigned int pointsCount, Vector3 * normal, Vector3 origin);

float PolygonArea(std::vector <Object::Point> points);


Vector3 crossProduct2Vectors(Vector3 VectorA, Vector3 VectorB);
inline Vector3 crossProduct3Points(Vector3 *arrayOfPoints) {
	Vector3 VectorA = arrayOfPoints[0] - arrayOfPoints[1];
	Vector3 VectorB = arrayOfPoints[2] - arrayOfPoints[1];

	return crossProduct2Vectors(VectorA, VectorB);
}
inline Vector3 crossProduct3Points(Vector3 p1, Vector3 p2, Vector3 p3) {
	Vector3 VectorA = p2 - p1;
	Vector3 VectorB = p2 - p3;

	return crossProduct2Vectors(VectorA, VectorB);
}
inline float DotProduct(Vector3 VectorA, Vector3 VectorB) {
	return VectorA.X*VectorB.X + VectorA.Y*VectorB.Y + VectorA.Z*VectorB.Z;
}


inline void MovePlane(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 movePoint) {
	for (size_t i = 0; i < pointsCount; i++)
	{
		arrayOfPoints[i] = arrayOfPoints[i] - movePoint;
	}
}
//https://stackoverflow.com/questions/9423621/3d-rotations-of-a-plane
inline void Plane3DTo2D(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 *normal, Vector3 origin) {
	//move to origin
	MovePlane(arrayOfPoints, pointsCount, origin);
	//calculate normal
	*normal = crossProduct3Points(arrayOfPoints).Normalize();
	Vector3 normal2D(0, 0, 1);
	if (*normal != normal2D) //same
	{
		double c /*costheta -*/ = DotProduct(*normal, normal2D);
		Vector3 axis = crossProduct2Vectors(*normal, normal2D);
		double s = sqrt(1 - c * c);
		double C = 1 - c;
		//rmat = matrix(	[x*x*C + c		x*y*C - z * s	x*z*C + y * s],
		//					[y*x*C + z * s  y*y*C + c	    y*z*C - x * s]
		//					[z*x*C - y * s  z*y*C + x * s	z*z*C + c])
		Matrix rotationMatrix = Matrix();
		rotationMatrix.m00 = (double)axis.X * (double)axis.X * C + c;					rotationMatrix.m01 = (double)axis.X * (double)axis.Y * C - axis.Z * s;			rotationMatrix.m02 = (double)axis.X * (double)axis.Z*C + axis.Y * s;
		rotationMatrix.m10 = (double)axis.Y * (double)axis.X * C + axis.Z * s;			rotationMatrix.m11 = (double)axis.Y * (double)axis.Y * C + c;					rotationMatrix.m12 = (double)axis.Y * (double)axis.Z*C - axis.X * s;
		rotationMatrix.m20 = (double)axis.Z * (double)axis.X * C - axis.Y * s;			rotationMatrix.m21 = (double)axis.Z * (double)axis.Y * C + axis.X * s;			rotationMatrix.m22 = (double)axis.Z * (double)axis.Z*C + c;

		//rotate points to 2D by rotating normal
		for (size_t i = 0; i < pointsCount; i++)
		{
			arrayOfPoints[i] = rotationMatrix * arrayOfPoints[i];
			//Vector3 Y = DotProduct(normal, crossProduct2Vectors(arrayOfPoints).Normalize());
		}
	}

}
inline void Plane3DTo2D(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 *normal) {
	Plane3DTo2D(arrayOfPoints, pointsCount, normal, arrayOfPoints[0]);
}
inline void Plane2DTo3D(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 *normal, Vector3 origin) {
	//rotate points to 2D by rotating normal
	Vector3 normal2D(0, 0, 1);

	if (*normal != normal2D) //same
	{
		double c /*costheta -*/ = DotProduct(normal2D, *normal);
		Vector3 axis = crossProduct2Vectors(normal2D, *normal);
		double s = sqrt(1 - c * c);
		double C = 1 - c;
		//rmat = matrix(	[x*x*C + c		x*y*C - z * s	x*z*C + y * s],
		//					[y*x*C + z * s  y*y*C + c	    y*z*C - x * s]
		//					[z*x*C - y * s  z*y*C + x * s	z*z*C + c])
		Matrix rotationMatrix = Matrix();
		rotationMatrix.m00 = (double)axis.X * (double)axis.X * C + c;							rotationMatrix.m01 = (double)axis.X * (double)axis.Y*C - (double)axis.Z * s;			rotationMatrix.m02 = (double)axis.X * (double)axis.Z*C + (double)axis.Y * s;
		rotationMatrix.m10 = (double)axis.Y * (double)axis.X * C + (double)axis.Z * s;			rotationMatrix.m11 = (double)axis.Y * (double)axis.Y*C + c;								rotationMatrix.m12 = (double)axis.Y * (double)axis.Z*C - (double)axis.X * s;
		rotationMatrix.m20 = (double)axis.Z * (double)axis.X * C - (double)axis.Y * s;			rotationMatrix.m21 = (double)axis.Z * (double)axis.Y*C + (double)axis.X * s;			rotationMatrix.m22 = (double)axis.Z * (double)axis.Z*C + c;

		for (size_t i = 0; i < pointsCount; i++)
		{
			arrayOfPoints[i] = rotationMatrix * arrayOfPoints[i];
		}
	}
	MovePlane(arrayOfPoints, pointsCount, Vector3(0, 0, 0) - origin);
}

inline float PolygonArea(std::vector<Object::Point> points)
{
	return 0.0f;
}

inline Vector3 PolygonCentroid(std::vector<Vector3> pointVec) {
	double sumX = 0;
	double sumY = 0;
	double sumZ = 0;
	for (size_t i = 0; i < pointVec.size(); i++)
	{
		sumX += pointVec[i].X;
		sumY += pointVec[i].Y;
		sumZ += pointVec[i].Z;
	}

	sumX /= pointVec.size();
	sumY /= pointVec.size();
	sumZ /= pointVec.size();

	return Vector3((float)sumX, (float)sumY, (float)sumZ) / 3;
}