#include "pch.h"

Vector3 crossProduct2Vectors(Vector3 VectorA, Vector3 VectorB);

Vector3 crossProduct3Points(Vector3 *arrayOfPoints);

Vector3 crossProduct3Points(Vector3 p1, Vector3 p2, Vector3 p3);

float DotProduct(Vector3 VectorA, Vector3 VectorB);

void Plane3DTo2D(Vector3 * arrayOfPoints, unsigned int pointsCount, Vector3 * normal);
void Plane3DTo2D(Vector3 * arrayOfPoints, unsigned int pointsCount, Vector3 * normal, Vector3 origin);

void Plane2DTo3D(Vector3 * arrayOfPoints, unsigned int pointsCount, Vector3 * normal, Vector3 origin);

