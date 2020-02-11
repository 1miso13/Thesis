#include "pch.h"
#include "Rectangle.h"
#include <glm/glm.hpp>

namespace Object {

	Rectangle::Rectangle(
		float height,
		float width,
		Vector3 planeVector,
		Point center,
		Vector3 normal) {
		this->center = center;
		this->height = height;
		this->width = width;
		this->planeVector = planeVector;
		this->normal = normal;
		GeometricType = RECTANGLE_ObjectType;
		CreateMesh();
	}
	Rectangle::~Rectangle()
	{
	}

	void Rectangle::CalculatePerimeter()
	{
		perimeter = (double)height + (double)height + (double)width + (double)width;
	}

	void Rectangle::CalculateArea()
	{
		area = (double)height * (double)width;
	}
	void Rectangle::CreateMesh() {
		glm::vec3 glmCenter(center.Position.X, center.Position.Y, center.Position.Z);
		glm::vec3 glmPlaneVector(planeVector.X, planeVector.Y, planeVector.Z);
		glm::vec3 glmNormal(normal.X, normal.Y, normal.Z);
		glmPlaneVector =	glm::normalize(glmPlaneVector);
		glmNormal =			glm::normalize(glmNormal);
		glm::vec3 glmPlaneVectorLeft=glm::normalize(glm::cross(glmNormal,glmPlaneVector));



		auto front = glmCenter + width * glmPlaneVector;
		auto back = glmCenter + -width * glmPlaneVector;

		auto leftFront  = front + height * glmPlaneVectorLeft;
		auto rightFront = front + -height * glmPlaneVectorLeft;

		auto leftBack  = back + height * -glmPlaneVectorLeft;
		auto rightBack = back + -height * -glmPlaneVectorLeft;


		vertices.push_back(leftFront.x);
		vertices.push_back(leftFront.y);
		vertices.push_back(leftFront.z);

		vertices.push_back(rightFront.x);
		vertices.push_back(rightFront.y);
		vertices.push_back(rightFront.z);

		vertices.push_back(leftBack.x);
		vertices.push_back(leftBack.y);
		vertices.push_back(leftBack.z);

		vertices.push_back(rightBack.x);
		vertices.push_back(rightBack.y);
		vertices.push_back(rightBack.z);

		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);

		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);

		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);

		normals.push_back(normal.X);
		normals.push_back(normal.Y);
		normals.push_back(normal.Z);


		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(0);

	}

}