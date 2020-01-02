#include "pch.h"
#include "Geometry.h"
#include <glm/glm.hpp>

 Vector3 crossProduct2Vectors(Vector3 VectorA, Vector3 VectorB) {
	auto c = glm::cross(glm::vec3(VectorA.X, VectorA.Y, VectorA.Z), glm::vec3(VectorB.X, VectorB.Y, VectorB.Z));

	return Vector3(c.x, c.y, c.z);//(X, Y, Z);
}