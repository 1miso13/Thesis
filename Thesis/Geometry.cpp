#include "pch.h"


using namespace std; 

Vector3 crossProduct2Vectors(Vector3 VectorA, Vector3 VectorB) {
	float X = VectorA.Y*VectorB.Z + VectorB.Y*VectorA.Z;
	float Y = VectorA.Z*VectorB.X + VectorB.Z*VectorA.X;
	float Z = VectorA.X*VectorB.Y + VectorB.X*VectorA.Y;

	return Vector3(X, Y, Z);
}
Vector3 crossProduct3Points(Vector3 *arrayOfPoints) {
	Vector3 VectorA = arrayOfPoints[1] - arrayOfPoints[0];
	Vector3 VectorB = arrayOfPoints[1] - arrayOfPoints[2];

	return crossProduct2Vectors(VectorA, VectorB);
}
Vector3 crossProduct3Points(Vector3 p1, Vector3 p2, Vector3 p3) {
	Vector3 VectorA = p2 - p1;
	Vector3 VectorB = p2 - p3;

	return crossProduct2Vectors(VectorA, VectorB);
}
float DotProduct(Vector3 VectorA, Vector3 VectorB) {
	return VectorA.X*VectorB.X + VectorA.Y*VectorB.Y + VectorA.Z*VectorB.Z;
}


void MovePlane(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 movePoint) {
	for (size_t i = 0; i < pointsCount; i++)
	{
		arrayOfPoints[i] = arrayOfPoints[i] - movePoint;
	}
}
//https://stackoverflow.com/questions/9423621/3d-rotations-of-a-plane
void Plane3DTo2D(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 *normal,Vector3 origin) {
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
		/*rmat = matrix(	[x*x*C + c		x*y*C - z * s	x*z*C + y * s],
							[y*x*C + z * s  y*y*C + c	    y*z*C - x * s]
							[z*x*C - y * s  z*y*C + x * s	z*z*C + c])*/
		Matrix rotationMatrix = Matrix();
		rotationMatrix.m00 = axis.X * axis.X *C + c;					rotationMatrix.m01 = axis.X * axis.Y*C - axis.Z * s;			rotationMatrix.m02 = axis.X * axis.Z*C + axis.Y * s;
		rotationMatrix.m10 = axis.Y * axis.X*C + axis.Z * s;			rotationMatrix.m11 = axis.Y * axis.Y*C + c;						rotationMatrix.m12 = axis.Y * axis.Z*C - axis.X * s;
		rotationMatrix.m20 = axis.Z * axis.X*C - axis.Y * s;			rotationMatrix.m21 = axis.Z * axis.Y*C + axis.X * s;			rotationMatrix.m22 = axis.Z * axis.Z*C + c;

		//rotate points to 2D by rotating normal
		for (size_t i = 0; i < pointsCount; i++)
		{
			arrayOfPoints[i] =  rotationMatrix*arrayOfPoints[i];
			//Vector3 Y = DotProduct(normal, crossProduct2Vectors(arrayOfPoints).Normalize());
		}
	}

}
void Plane3DTo2D(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 *normal) {
	Plane3DTo2D(arrayOfPoints, pointsCount, normal, arrayOfPoints[0]);
}
void Plane2DTo3D(Vector3 *arrayOfPoints, unsigned int pointsCount, Vector3 *normal, Vector3 origin) {
	//rotate points to 2D by rotating normal
	Vector3 normal2D(0, 0, 1);

	if (*normal != normal2D) //same
	{
		double c /*costheta -*/ = DotProduct(normal2D, *normal);
		Vector3 axis = crossProduct2Vectors(normal2D, *normal);
		double s = sqrt(1 - c * c);
		double C = 1 - c;
		/*rmat = matrix(	[x*x*C + c		x*y*C - z * s	x*z*C + y * s],
							[y*x*C + z * s  y*y*C + c	    y*z*C - x * s]
							[z*x*C - y * s  z*y*C + x * s	z*z*C + c])*/
		Matrix rotationMatrix = Matrix();
		rotationMatrix.m00 = axis.X * axis.X *C + c;					rotationMatrix.m01 = axis.X * axis.Y*C - axis.Z * s;			rotationMatrix.m02 = axis.X * axis.Z*C + axis.Y * s;
		rotationMatrix.m10 = axis.Y * axis.X*C + axis.Z * s;			rotationMatrix.m11 = axis.Y * axis.Y*C + c;						rotationMatrix.m12 = axis.Y * axis.Z*C - axis.X * s;
		rotationMatrix.m20 = axis.Z * axis.X*C - axis.Y * s;			rotationMatrix.m21 = axis.Z * axis.Y*C + axis.X * s;			rotationMatrix.m22 = axis.Z * axis.Z*C + c;

		for (size_t i = 0; i < pointsCount; i++)
		{
			arrayOfPoints[i] = rotationMatrix * arrayOfPoints[i];
		}
	}
	MovePlane(arrayOfPoints, pointsCount, Vector3(0,0,0)-origin);
}
