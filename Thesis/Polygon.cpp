#include "pch.h"
#include "Polygon.h"
#include "Point.h"

#include "EarClippingTriangulator.h"

namespace Object {

	Polygon::Polygon(std::vector <Point> points) {
		GeometricType = POLYGON_ObjectType;
		this->points = points;

		this->normal = crossProduct3Points(points[0].Position, points[1].Position, points[2].Position).Normalize();



		double sumX = 0;
		double sumY = 0;
		double sumZ = 0;
		for (size_t i = 0; i < points.size(); i++)
		{
			sumX += points[i].Position.X;
			sumY += points[i].Position.Y;
			sumZ += points[i].Position.Z;
		}

		sumX /= points.size();
		sumY /= points.size();
		sumZ /= points.size();

		this->center = Point((float)sumX, (float)sumY, (float)sumZ) / 3;

		CreateMesh();
	}

	Polygon::~Polygon() {

	}
	void Polygon::CalculatePerimeter() {
		perimeter += (points[points.size() - 1] - points[0]).Distance();
		for (size_t i = 1; i < points.size(); i++)
		{
			perimeter += (points[i] - points[i - 1]).Distance();
		}
	}
	void Polygon::CalculateArea() {
		area = PolygonArea(points);
	}

	void Polygon::CreateMesh() {
		for (size_t i = 0; i < points.size(); i++)
		{
			vertices.push_back(points[i].Position.X);
			vertices.push_back(points[i].Position.Y);
			vertices.push_back(points[i].Position.Z);
		}
		std::vector <glm::vec3> verticesGLM;
		for (size_t i = 0; i < vertices.size(); i+=3)
		{
			verticesGLM.push_back(glm::vec3(vertices[i], vertices[i+1], vertices[i+2]));
		}
		EarClippingTriangulator triangulator;
		triangulator.Init(&verticesGLM,&indices);
		triangulator.Triangulate();
		for (size_t i = 0; i < vertices.size()/3; i++)
		{
			normals.push_back(normal.X);
			normals.push_back(normal.Y);
			normals.push_back(normal.Z);
		}
	}
}