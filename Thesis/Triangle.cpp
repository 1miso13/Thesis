#include "pch.h"
#include "Geometry.h"
#include "Triangle.h"
#include "Point.h"
#include "Vector.h"

namespace Object {
	Triangle::Triangle(Point p1, Point p2, Point p3)
	{
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		Initialize();
	}

	void Triangle::Initialize() {
		Vector3 AB = p2 - p1;
		Vector3 AC = p3 - p1;
		normal = crossProduct2Vectors(AB, AC).Normalize();
		center = ((p1 + p2 + p3) / 3);
		GeometricType = TRIANGLE_ObjectType;
		CreateMesh();
	}

	Triangle::~Triangle()
	{
	}

	void Triangle::CalculatePerimeter()
	{
		float a = (p2 - p1).Distance();
		float b = (p3 - p2).Distance();
		float c = (p1 - p3).Distance();

		perimeter = (double)a + (double)b + (double)c;
	}

	void Triangle::CalculateArea()
	{
		Vector3 AB = p2 - p1;
		Vector3 AC = p3 - p1;
		area = crossProduct2Vectors(AB, AC).Distance() / 2;
	}
	void Triangle::CreateMesh() {
		vertices.push_back(p1.Position.X);
		vertices.push_back(p1.Position.Y);
		vertices.push_back(p1.Position.Z);
		vertices.push_back(p2.Position.X);
		vertices.push_back(p2.Position.Y);
		vertices.push_back(p2.Position.Z);
		vertices.push_back(p3.Position.X);
		vertices.push_back(p3.Position.Y);
		vertices.push_back(p3.Position.Z);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);

		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);

		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);
	}

	void Triangle::setP1(Point p) {
		this->p1 = p;
	}
	void Triangle::setP1(float x, float y, float z) {
		this->p1.Position.X = x;
		this->p1.Position.Y = y;
		this->p1.Position.Z = z;
	}
	void Triangle::setP2(Point p) {
		this->p2 = p;
	}
	void Triangle::setP2(float x, float y, float z) {
		this->p2.Position.X = x;
		this->p2.Position.Y = y;
		this->p2.Position.Z = z;
	}
	void Triangle::setP3(Point p) {
		this->p3 = p;
	}
	void Triangle::setP3(float x, float y, float z) {
		this->p3.Position.X = x;
		this->p3.Position.Y = y;
		this->p3.Position.Z = z;
	}

}