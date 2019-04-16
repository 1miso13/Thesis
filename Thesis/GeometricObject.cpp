#include "pch.h"
#include "GeometricObject.h"
#include <glm/glm.hpp>
//
//std::string GeometricObject::TypeToText()
//{
//	switch (GeometricType)
//	{
//	case POINTObjectType:
//		return "Point";
//	case LINE:
//		return "Line";
//	case SURFACE:
//		return "Surface";
//	case CIRCLE:
//		return "Circle";
//	case RECTANGLE:
//		return "Rectangle";
//	case POLYGON:
//		return "Polygon";
//	case TRIANGLE:
//		return "Triangle";
//	case OBJECT3D:
//		return "3D object";
//	case PYRAMID:
//		return "Pyramid";
//	case SPHERE:
//		return "Sphere";
//	case INVALIDObjectType:
//		return "Invalid";
//	default:
//		break;
//	}
//	return std::string();
//}
namespace Object {
	float VectorAngle(glm::vec3 A,glm::vec3 B) {
		return glm::acos(glm::dot(A, B));//radians
	}
	void GeometricObject::calcVertexNormals(std::vector<unsigned int> indices, size_t indiciesCount, std::vector <float> vertex, std::vector <float> *verticesNormal, size_t vertexCount, void *triangleNormal)
	{
		std::vector <double> verticesNormaldouble;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verticesNormaldouble.push_back(0);
			verticesNormaldouble.push_back(0);
			verticesNormaldouble.push_back(1);
		}
		size_t count = indiciesCount / 3;
		//vertex
		for (size_t i = 0; i < count; i++)
		{
			glm::vec3 PointA(vertex[indices[i * 3	 ] * 3 + 0], vertex[indices[i * 3	 ] * 3 + 1], vertex[indices[i * 3	 ] * 3 + 2]);
			glm::vec3 PointB(vertex[indices[i * 3 + 1] * 3 + 0], vertex[indices[i * 3 + 1] * 3 + 1], vertex[indices[i * 3 + 1] * 3 + 2]);
			glm::vec3 PointC(vertex[indices[i * 3 + 2] * 3 + 0], vertex[indices[i * 3 + 2] * 3 + 1], vertex[indices[i * 3 + 2] * 3 + 2]);
			//1st triangle index
			//X
			(verticesNormaldouble)[indices[i * 3] * 3 + 0] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].x
				* VectorAngle(
					PointB - PointA,
					PointC - PointA);
			//Y
			(verticesNormaldouble)[indices[i * 3] * 3 + 1] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].y
				* VectorAngle(
					PointB - PointA,
					PointC - PointA);
			//Z
			(verticesNormaldouble)[indices[i * 3] * 3 + 2] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].z
				* VectorAngle(
					PointB - PointA,
					PointC - PointA);
			//2nd triangle index
			//X
			(verticesNormaldouble)[indices[i * 3 + 1] * 3 + 0] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].x
				* VectorAngle(
					PointC - PointB,
					PointA - PointB);
			//Y
			(verticesNormaldouble)[indices[i * 3 + 1] * 3 + 1] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].y
				* VectorAngle(
					PointC - PointB,
					PointA - PointB);
			//Z
			(verticesNormaldouble)[indices[i * 3 + 1] * 3 + 2] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].z
				* VectorAngle(
					PointC - PointB,
					PointA - PointB);
			//3rd triangle index
			//X
			(verticesNormaldouble)[indices[i * 3 + 2] * 3 + 0] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].x
				* VectorAngle(
					PointA - PointC,
					PointB - PointC);
			//Y
			(verticesNormaldouble)[indices[i * 3 + 2] * 3 + 1] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].y
				* VectorAngle(
					PointA - PointC,
					PointB - PointC);
			//Z
			(verticesNormaldouble)[indices[i * 3 + 2] * 3 + 2] +=
				((*((std::vector<glm::vec3>*)triangleNormal)))[i].z
				* VectorAngle(
					PointA - PointC,
					PointB - PointC);
		}
		//normalize
		for (size_t i = 0; i < vertexCount; i++)
		{
			auto normalized = -glm::normalize(glm::vec3((verticesNormaldouble)[i], (verticesNormaldouble)[i+1], (verticesNormaldouble)[i+2]));
			(*verticesNormal).push_back(normalized.x);
			(*verticesNormal).push_back(normalized.y);
			(*verticesNormal).push_back(normalized.z);
		}
	}
	void GeometricObject::calcTriangleNormals(std::vector<unsigned int >indices, size_t indiciesCount, std::vector<float> vertex,void  *triangleNormal) {
		size_t count = indiciesCount / 3;
		for (size_t i = 0, j; i < count; i++)
		{
			//Vec3 BA = C - B;
			//Vec3 BC = A - B;

			auto Aindex = indices[i * 3 + 0] * 3;
			auto Bindex = indices[i * 3 + 1] * 3;
			auto Cindex = indices[i * 3 + 2] * 3;
			glm::vec3 A = glm::vec3(vertex[Aindex], vertex[Aindex + 1], vertex[Aindex + 2]);
			glm::vec3 B = glm::vec3(vertex[Bindex], vertex[Bindex + 1], vertex[Bindex + 2]);
			glm::vec3 C = glm::vec3(vertex[Cindex], vertex[Cindex + 1], vertex[Cindex + 2]);

			//(*triangleNormal)[i] = normalize(cross(vertex[indices[i * 3]], vertex[indices[i * 3 + 1]], vertex[indices[i * 3 + 2]]));
			auto vec= glm::normalize(glm::cross(C-A,A-B));
			(*((std::vector<glm::vec3>*)triangleNormal))[i] = vec;

		}
		
	}
	void GeometricObject::calculateNormals() {
		std::vector <glm::vec3> triangleNormals;
		for (size_t i = 0; i < indices.size()/3; i++)
		{
			triangleNormals.push_back(glm::vec3());
		}
		//for (size_t i = 0; i < vertices.size(); i++)
		//{
		//	normals.push_back(0);//X
		//	normals.push_back(0);//Y
		//	normals.push_back(1);//Z
		//}
		calcTriangleNormals(indices, indices.size(), vertices, (void*)&triangleNormals);
		calcVertexNormals(indices, indices.size(), vertices,&normals, vertices.size(), (void*)&triangleNormals);
	}
}