#include "pch.h"
#include "CalculateMeshNormals.h"
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

float angleVec(glm::vec3 x, glm::vec3 y) {
	float A = glm::dot(glm::normalize(x), glm::normalize(y));
	float B = glm::clamp(A, -1.f, (1.f));
	float C = glm::acos(B);
	return C;
}
void CalculateMeshNormals::calculateNormals(std::vector<int>* indicesR, std::vector <float>* verticesR, std::vector<int> *indices, std::vector <float> *vertices, std::vector <float> *verticesNormal)
{
	indices->clear();
	vertices->clear();
	verticesNormal->clear();
	for (size_t i = 0; i < indicesR->size(); i+=3)
	{
		indices->push_back(i);
		indices->push_back(i+1);
		indices->push_back(i+2);
		float p1x = verticesR->at(indicesR->at(i)*3+0);
		float p1y = verticesR->at(indicesR->at(i)*3+1);
		float p1z = verticesR->at(indicesR->at(i)*3+2);
		float p2x = verticesR->at(indicesR->at(i + 1)*3 + 0);
		float p2y = verticesR->at(indicesR->at(i + 1)*3 + 1);
		float p2z = verticesR->at(indicesR->at(i + 1)*3 + 2);
		float p3x = verticesR->at(indicesR->at(i + 2)*3 + 0);
		float p3y = verticesR->at(indicesR->at(i + 2)*3 + 1);
		float p3z = verticesR->at(indicesR->at(i + 2)*3 + 2);
		vertices->push_back(p1x);
		vertices->push_back(p1y);
		vertices->push_back(p1z);
		vertices->push_back(p2x);
		vertices->push_back(p2y);
		vertices->push_back(p2z);
		vertices->push_back(p3x);
		vertices->push_back(p3y);
		vertices->push_back(p3z);
		glm::vec3 x = glm::normalize(glm::cross(glm::vec3(p2x - p1x, p2y - p1y, p2z - p1z), glm::vec3(p3x - p1x, p3y - p1y, p3z - p1z)));
		verticesNormal->push_back(x.x);
		verticesNormal->push_back(x.y);
		verticesNormal->push_back(x.z);
		verticesNormal->push_back(x.x);
		verticesNormal->push_back(x.y);
		verticesNormal->push_back(x.z);
		verticesNormal->push_back(x.x);
		verticesNormal->push_back(x.y);
		verticesNormal->push_back(x.z);
	}
	/*glm::vec3 * v = reinterpret_cast<glm::vec3*>(vertex.data());
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
		/*vn[indices[i * 3]] = 	//p1
			glm::vec3 av1 = v[indices[i * 3 + 1]] - v[indices[i * 3]];
			glm::vec3 av2 = v[indices[i * 3 + 2]] - v[indices[i * 3]];
			float angleA = angleVec(av1,av2
				); 
			glm::vec3 a =
				triangleNormal
				* angleA;
		//*vn[indices[i * 3 + 1]] = ///p2
			float angleB = angleVec(
				v[indices[i * 3 + 2]] - v[indices[i * 3 + 1]],
				v[indices[i * 3]] - v[indices[i * 3 + 1]]);
			glm::vec3 b =
				triangleNormal
				* angleB;
		//*vn[indices[i * 3 + 2]] = ///p3
			float angleC = angleVec(
				v[indices[i * 3]] - v[indices[i * 3 + 2]],
				v[indices[i * 3 + 1]] - v[indices[i * 3 + 2]]);
			glm::vec3 c =
				triangleNormal
				* angleC;
			verticesNormal->at(indices[i * 3]) = a.x;
			verticesNormal->at(indices[i * 3] + 1) = a.y;
			verticesNormal->at(indices[i * 3] + 2) = a.z;
			verticesNormal->at(indices[i * 3+1]) =	 b.x;
			verticesNormal->at(indices[i * 3+1] + 1) = b.y;
			verticesNormal->at(indices[i * 3+1] + 2) = b.z;
			verticesNormal->at(indices[i * 3+2]) =	 c.x;
			verticesNormal->at(indices[i * 3+2] + 1) = c.y;
			verticesNormal->at(indices[i * 3+2] + 2) = c.z;

	}
	//normalize
	count = vertex.size() / 3;
	for (size_t i = 0; i < count; i++)
	{
		vn[i] = glm::normalize(vn[i]);
	}*/
}