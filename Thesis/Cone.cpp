
#include "pch.h"
#include "Cone.h"
#include "Geometry.h"
#include "Polygon.h"

#include <glm/glm.hpp>
#define M_PI           3.14159265358979323846
#define INTEGRAL_STEP_COUNT 100

namespace Object {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="apex"></param>
	/// <param name="base"></param>
	Cone::Cone(Point apex, Surface * base)
	{
		this->apex = apex;
		this->base = base;
		this->BaseType = GetBaseType();
		CalculateHeight();
		GeometricType = Cone_ObjectType;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="height"></param>
	/// <param name="base"></param>
	/// <param name="BaseType">1-circle
	/// 2-triangle
	/// 3-rectangle
	/// 4-polygon</param>
	Object::Cone::Cone(float height, Surface * base)
	{
		this->height = height;
		this->apex = Point(base->center) + base->normal*height;
		this->base = base;
		this->BaseType = GetBaseType();
		GeometricType = Cone_ObjectType;

		CreateMesh();
	}

	Object::Cone::~Cone()
	{
	}

	/// <summary>
	/// If not entered 
	/// </summary>
	void Object::Cone::CalculateHeight()
	{
		double distPointToPlane = DotProduct((this->apex.Position - this->base->center), this->base->normal);
		Point p2 = this->apex.Position - (this->base->normal * distPointToPlane);
		height = Line(p2, this->apex).Distance();
	}

	void Object::Cone::CalculateVolume()
	{
		volume = base->GetArea() * height * 1 / 3;
	}

	void Object::Cone::CalculateSurfaceArea()
	{
		surfaceArea = base->GetArea();

		//rozdielne pre rozdielne tvary
		if (BaseType == 1) {// circle

			//Tato metoda je nepresna!
			//kruhovu zakladnu rozdelime na N casti
			//každú èas spojíme s vrcholom
			//vznikne N trojuholniko
			//vypocitame a scitame plochu trojuholnikov
			Vector3 perpendicularVector = Vector3(base->normal.Y, -base->normal.X, 0) * ((Circle*)base)->radius;

			double stepAlpha = M_PI / INTEGRAL_STEP_COUNT;
			double alpha = 0;
			for (size_t i = 0; i < INTEGRAL_STEP_COUNT; i++)
			{
				Vector3 AB = (this->base->center + (cos(alpha)*perpendicularVector + (sin(alpha))*crossProduct2Vectors(base->normal, perpendicularVector))) - this->apex;
				Vector3 AC = (this->base->center + (cos(alpha + stepAlpha)*perpendicularVector + (sin(alpha + stepAlpha))*crossProduct2Vectors(base->normal, perpendicularVector))) - this->apex;
				surfaceArea += crossProduct2Vectors(AB, AC).Distance() / 2;
				alpha += stepAlpha;
			}

		}
		else
			if (BaseType == 2)//triangle
			{

				Vector3 AA = ((Triangle*)base)->p1 - this->apex;
				Vector3 BA = ((Triangle*)base)->p1 - this->apex;
				Vector3 CA = ((Triangle*)base)->p3 - this->apex;
				surfaceArea += crossProduct2Vectors(AA, BA).Distance() / 2;
				surfaceArea += crossProduct2Vectors(BA, CA).Distance() / 2;
				surfaceArea += crossProduct2Vectors(CA, AA).Distance() / 2;
			}
			else
				if (BaseType == 3)//rectangle
				{
					//TODO rectangle base Cone - surface area

				}
				else
					if (BaseType == 4)//polygon
					{

						Object::Polygon* basePolygon = (Object::Polygon*)base;
						for (size_t i = 1; i < basePolygon->points.size(); i++)
						{
							Vector3 AA = basePolygon->points[i - 1] - this->apex;
							Vector3 BA = basePolygon->points[i] - this->apex;
							surfaceArea += crossProduct2Vectors(AA, BA).Distance() / 2;
						}

						Vector3 AA = basePolygon->points[basePolygon->points.size() - 1] - this->apex;
						Vector3 BA = basePolygon->points[0] - this->apex;
						surfaceArea += crossProduct2Vectors(AA, BA).Distance() / 2;
					}
	}

	short Object::Cone::GetBaseType()
	{
		/// 1-circle
		/// 2-triangle
		/// 3-rectangle
		/// 4-polygon
		switch (base->GeometricType)
		{
		case Object::ObjectTypeEnum::CIRCLE_ObjectType:
			return 1;
		case Object::ObjectTypeEnum::TRIANGLE_ObjectType:
			return 2;
		case Object::ObjectTypeEnum::RECTANGLE_ObjectType:
			return 3;
		case Object::ObjectTypeEnum::POLYGON_ObjectType:
			return 4;
		default:
			break;
		}
		return 0;
	}
	void Cone::CreateMesh() {
		//std::vector<float> vertices;
		//std::vector<float> normals;
		//std::vector<unsigned> indices;

		//if base normal is pointing to apex, rotate base verticies to oposite direction
		bool base_normal_is_pointing_toward_Apex = 0 < glm::dot(
				glm::vec3(
					base->vertices.at(0),
					base->vertices.at(1),
					base->vertices.at(2))
			-
				glm::vec3(
					base->normal.X,
					base->normal.Y,
					base->normal.Z)
		,
				glm::vec3(
					apex.Position.X,
					apex.Position.Y,
					apex.Position.Z)
			-
				glm::vec3(
					base->normal.X,
					base->normal.Y,
					base->normal.Z)
		);
		//base verticies
		for (size_t i = 0; i < base->vertices.size(); i++)
		{
			vertices.push_back(base->vertices[i]);
		}
		for (size_t i = 0; i < base->normals.size(); i++)
		{
			normals.push_back(base->normals[i]);
		}
		for (size_t i = 0; i < base->indices.size(); i++)
		{
			indices.push_back(base->indices[i]);
		}
		if (base_normal_is_pointing_toward_Apex)
		{
			std::reverse(normals.begin(),normals.end());
		}

		size_t j = (base->vertices.size())/3- (size_t)1;
		size_t baseVerticies_count = base->vertices.size() / 3;
		for (size_t i = 0; i < baseVerticies_count; i++)
		{
			//apex
			vertices.push_back(base->vertices.at(j * 3 + 0));
			vertices.push_back(base->vertices.at(j * 3 + 1));
			vertices.push_back(base->vertices.at(j * 3 + 2));
			vertices.push_back(base->vertices.at(i * 3 + 0));
			vertices.push_back(base->vertices.at(i * 3 + 1));
			vertices.push_back(base->vertices.at(i * 3 + 2));
			vertices.push_back(apex.Position.X);
			vertices.push_back(apex.Position.Y);
			vertices.push_back(apex.Position.Z);


			indices.push_back((int)baseVerticies_count + i * 3 + 0);
			indices.push_back((int)baseVerticies_count + i * 3 + 1);
			indices.push_back((int)baseVerticies_count + i * 3 + 2);

			glm::vec3 a = glm::vec3(base->vertices[j * (size_t)3 + (size_t)0], base->vertices[j * (size_t)3 + (size_t)1], base->vertices[j * (size_t)3 + (size_t)2]);
			glm::vec3 b = glm::vec3(base->vertices[i * (size_t)3 + (size_t)0], base->vertices[i * (size_t)3 + (size_t)1], base->vertices[i * (size_t)3 + (size_t)2]);
			glm::vec3 c = glm::vec3(apex.Position.X, apex.Position.Y, apex.Position.Z);
			glm::vec3 normal = glm::normalize(cross(a-b,c-b));

			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);

			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);

			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
			j = i;
		}

		//verticesR
		for (size_t i = 0; i < vertices.size(); i++)
		{
			verticesR.push_back(vertices.at(i));
		}
		//indicesR
		for (size_t i = 0; i < indices.size(); i++)
		{
			indicesR.push_back(indices.at(i));
		}
		//apex
		verticesR.push_back(apex.Position.X);
		verticesR.push_back(apex.Position.Y);
		verticesR.push_back(apex.Position.Z);
		for (size_t i = 0; i < baseVerticies_count; i++)
		{
			indicesR.push_back((int)j);
			indicesR.push_back((int)i);
			indicesR.push_back((int)baseVerticies_count);
		}
		
	}
}