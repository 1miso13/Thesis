#include "pch.h"
#include "Circle.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <fstream>
namespace Object {
	Circle::Circle(Point center, float radius, Vector3 normal) {
		this->center = center;
		this->radius = radius;
		this->normal = normal;
		GeometricType = CIRCLE_ObjectType;
		CreateMesh();
	}
	void Circle::CalculatePerimeter()
	{
		perimeter = 2 * (4. * atan(1.))/*PI*/ * radius;
	}

	void Circle::CalculateArea()
	{
		area = (4. * atan(1.)) * radius * radius;
	}
	void Circle::CreateMesh() {
		
		//rotate
		const glm::vec3 a = glm::vec3(normal.X, normal.Y, normal.Z);
		const glm::vec3 b = glm::vec3(0, 1, 0); //up
		glm::vec3 v = glm::cross(b, a);
		float angle = acos(glm::dot(b, a) / (glm::length(b) * glm::length(a)));
		glm::mat4 rotmat = glm::rotate(angle, v);
		int N = 100;
		for (int n = 0; n < N; n++)
		{
			glm::vec4 circlePoint = rotmat * glm::vec4(cos(2 * glm::pi<float>() * n / N), 0, sin(2 * glm::pi<float>() * n / N), 0);
									


			vertices.push_back(radius * circlePoint.x/* + center.Position.X*/);//X
			vertices.push_back(radius * circlePoint.y/* + center.Position.Y*/);//Y
			vertices.push_back(radius * circlePoint.z /*+ center.Position.Z*/);//Z

			normals.push_back(normal.X);
			normals.push_back(normal.Y);
			normals.push_back(normal.Z);
		}
		for (size_t i = 2; i < N; i++)
		{
			indices.push_back(0);
			indices.push_back((int)i - 1);
			indices.push_back((int)i);
		}

		N = 1;
	}

}