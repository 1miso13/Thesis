#include "pch.h"
#include "CalculateMeshNormals.h"
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

void CalculateMeshNormals::calculateNormals(std::vector<int> indices, std::vector <float> vertex, std::vector <float> *verticesNormal)
{
	glm::vec3 * v = reinterpret_cast<glm::vec3*>(vertex.data());
	if (verticesNormal!=NULL)
	{
		verticesNormal->clear();
	}
	*verticesNormal = std::vector <float>(vertex.size(),0);
	glm::vec3 * vn = reinterpret_cast<glm::vec3*>(verticesNormal->data());
	size_t count = indices.size() / 3;
	for (size_t i = 0, j; i < count; i++)
	{
		glm::vec3 triangleNormal = glm::normalize(glm::cross(v[indices[i * 3 + 2]] - v[indices[i * 3]], v[indices[i * 3 + 1]] - v[indices[i * 3]])); //cross(v[indicies[i * 3]], v[indicies[i * 3 + 1]], v[indicies[i * 3 + 2]]));

	//vertex
		vn[indices[i * 3]] = 		//p1
			triangleNormal
			* angle(
				v[indices[i * 3 + 1]] - v[indices[i * 3]],
				v[indices[i * 3 + 2]] - v[indices[i * 3]]);
		vn[indices[i * 3 + 1]] = //p2
			triangleNormal
			* angle(
				v[indices[i * 3 + 2]] - v[indices[i * 3 + 1]],
				v[indices[i * 3]] - v[indices[i * 3 + 1]]);
		vn[indices[i * 3 + 2]] =  //p3
			triangleNormal
			* angle(
				v[indices[i * 3]] - v[indices[i * 3 + 2]],
				v[indices[i * 3 + 1]] - v[indices[i * 3 + 2]]);
	}
	//normalize
	count = vertex.size() / 3;
	for (size_t i = 0; i < count; i++)
	{
		vn[i] = glm::normalize(vn[i]);
	}
}