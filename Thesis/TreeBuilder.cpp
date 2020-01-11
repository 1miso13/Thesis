#include "pch.h"
#include "TreeBuilder.h"
#include <string>
#include "Shape3D.h"
#include "Pyramid.h"
#include "Sphere.h"


#include <chrono>
#include <glm/glm.hpp>

Object::GeometricObject * TreeBuilder::Extrude(Object::Surface *s, float distance) {
	auto RetObject = new Object::Shape3D();
	Object::Shape3D* RerObjectShape = (Object::Shape3D*)RetObject;
	//copy surface points 

	for (size_t i = 0; i < s->vertices.size(); i++)
	{
		RerObjectShape->vertices.push_back(s->vertices[i]);
	}
	for (size_t i = 0; i < s->indices.size(); i++)
	{
		RerObjectShape->indices.push_back(s->indices[i]);
	}

	//surface points duplicities move by surface normal 
	for (size_t i = 0; i < s->vertices.size(); i += 3)
	{
		RerObjectShape->vertices.push_back(s->vertices[i] + s->normal.X * distance);
		RerObjectShape->vertices.push_back(s->vertices[i + 1] + s->normal.Y * distance);
		RerObjectShape->vertices.push_back(s->vertices[i + 2] + s->normal.Z * distance);
	}
	for (size_t i = 0; i < s->indices.size(); i++)
	{
		RerObjectShape->indices.push_back(s->indices[i] + (unsigned int)s->vertices.size() / 3);
	}
	//normals
	//base - invert base normal
	for (size_t i = 0; i < s->normals.size(); i++)
	{
		RerObjectShape->normals.push_back(s->normals[i] * (distance >= 0 ? -1 : 1));
	}
	//top - base normal
	for (size_t i = 0; i < s->normals.size(); i++)
	{
		RerObjectShape->normals.push_back(s->normals[i] * (distance >= 0 ? 1 : -1));
	}


	//side
	int j = ((int)s->vertices.size())-3;
	for (unsigned int i = 0; i < s->vertices.size(); i += 3)
	{
		//	1*			top		- before actual
		//	 * *
		//	2* * *3		base	- before actual	-	actual
		RerObjectShape->vertices.push_back(s->vertices[j+ 0] + s->normal.X * distance);
		RerObjectShape->vertices.push_back(s->vertices[j+ 1] + s->normal.Y * distance);
		RerObjectShape->vertices.push_back(s->vertices[j+ 2] + s->normal.Z * distance);
		RerObjectShape->vertices.push_back(s->vertices[j+ 0]);
		RerObjectShape->vertices.push_back(s->vertices[j+ 1]);
		RerObjectShape->vertices.push_back(s->vertices[j+ 2]);
		RerObjectShape->vertices.push_back(s->vertices[i+ 0]);
		RerObjectShape->vertices.push_back(s->vertices[i+ 1]);
		RerObjectShape->vertices.push_back(s->vertices[i+ 2]);


		////	1* * *3		top		- before actual	-	actual
		////	   * *
		////	     *2		base	- actual
		RerObjectShape->vertices.push_back(s->vertices[j + 0] + s->normal.X * distance);
		RerObjectShape->vertices.push_back(s->vertices[j + 1] + s->normal.Y * distance);
		RerObjectShape->vertices.push_back(s->vertices[j + 2] + s->normal.Z * distance);
		RerObjectShape->vertices.push_back(s->vertices[i + 0]);
		RerObjectShape->vertices.push_back(s->vertices[i + 1]);
		RerObjectShape->vertices.push_back(s->vertices[i + 2]);
		RerObjectShape->vertices.push_back(s->vertices[i + 0] + s->normal.X * distance);
		RerObjectShape->vertices.push_back(s->vertices[i + 1] + s->normal.Y * distance);
		RerObjectShape->vertices.push_back(s->vertices[i + 2] + s->normal.Z * distance);

		RerObjectShape->indices.push_back(2 * (unsigned int) s->vertices.size() / 3 + i * 2);
		RerObjectShape->indices.push_back(2 * (unsigned int) s->vertices.size() / 3 + i * 2 + 1);
		RerObjectShape->indices.push_back(2 * (unsigned int) s->vertices.size() / 3 + i * 2 + 2);

		RerObjectShape->indices.push_back(2 * (unsigned int) s->vertices.size() / 3 + i * 2 + 3);
		RerObjectShape->indices.push_back(2 * (unsigned int) s->vertices.size() / 3 + i * 2 + 4);
		RerObjectShape->indices.push_back(2 * (unsigned int) s->vertices.size() / 3 + i * 2 + 5);


		glm::vec3 T1A(
			s->vertices[j + 0] + s->normal.X * distance,
			s->vertices[j + 1] + s->normal.Y * distance,
			s->vertices[j + 2] + s->normal.Z * distance);
		glm::vec3 T1B(
			s->vertices[j + 0],
			s->vertices[j + 1],
			s->vertices[j + 2]);
		glm::vec3 T1C(
			s->vertices[i + 0],
			s->vertices[i + 1],
			s->vertices[i + 2]);

		auto normal1 = glm::normalize(glm::cross(T1A-T1B,T1C-T1B));


		RerObjectShape->normals.push_back(normal1.x);
		RerObjectShape->normals.push_back(normal1.y);
		RerObjectShape->normals.push_back(normal1.z);

		RerObjectShape->normals.push_back(normal1.x);
		RerObjectShape->normals.push_back(normal1.y);
		RerObjectShape->normals.push_back(normal1.z);

		RerObjectShape->normals.push_back(normal1.x);
		RerObjectShape->normals.push_back(normal1.y);
		RerObjectShape->normals.push_back(normal1.z);
		

		glm::vec3 T2A(
			s->vertices[j + 0] + s->normal.X * distance,
			s->vertices[j + 1] + s->normal.Y * distance,
			s->vertices[j + 2] + s->normal.Z * distance);
		glm::vec3 T2B(
			s->vertices[i + 0],
			s->vertices[i + 1],
			s->vertices[i + 2]);
		glm::vec3 T2C(
			s->vertices[i + 0] + s->normal.X * distance,
			s->vertices[i + 1] + s->normal.Y * distance,
			s->vertices[i + 2] + s->normal.Z * distance);

		auto normal2 = glm::normalize(glm::cross(T2A - T2B, T2C - T2B));


		RerObjectShape->normals.push_back(normal2.x);
		RerObjectShape->normals.push_back(normal2.y);
		RerObjectShape->normals.push_back(normal2.z);

		RerObjectShape->normals.push_back(normal2.x);
		RerObjectShape->normals.push_back(normal2.y);
		RerObjectShape->normals.push_back(normal2.z);

		RerObjectShape->normals.push_back(normal2.x);
		RerObjectShape->normals.push_back(normal2.y);
		RerObjectShape->normals.push_back(normal2.z);


		j = i;
	}

	RetObject = RerObjectShape;
	return RetObject;
}
std::chrono::time_point< std::chrono::steady_clock> LastTime = std::chrono::steady_clock::now();
void TreeBuilder::Build() {
	//clear objects

		//for (size_t i = Objects->size(); i >0; i--)
		////for (size_t i = 0; i < Objects->size(); i++)
		//{
		//	try
		//	{
		//		/*delete*/ Objects->at(i-1)->Delete();
		//	}
		//	catch (...)
		//	{
		//	//	printf_s("Unable to delete object %d",i-1);
		//	}
		//}

	//if rebuild is needed, remove all objects
	//Objects->clear(); TODO
	//ObjectMap->clear();

	//remove all objects which operation no longer exists
	for (size_t i = 0; i < Objects->size(); i++)
	{
		if ((OperationMap->at(Objects->at(i)->ObjectName)) == NULL)
		{
			Object::GeometricObject* obj = ObjectMap->at(Objects->at(i)->ObjectName);
			Objects->erase(std::find(Objects->begin(), Objects->end(), obj));
			ObjectMap->erase(obj->ObjectName);
			obj->Delete();//delete TODO
		}
	}

	//set time
	if (!manualTimer)
	{
		//initialize timer
		if (needToInitializeTime)
		{
			needToInitializeTime = false;
			LastTime =std::chrono::steady_clock::now();
		}
		
		auto  actualTime = std::chrono::steady_clock::now();
		timeMiliseconds += std::chrono::duration_cast<std::chrono::milliseconds>(actualTime - LastTime).count();
		LastTime = actualTime;
	}


	Object::GeometricObject * o = NULL;
	//Create new objects
	for (size_t i = 0; i < OperationsVec->size(); i++)
	{
		if ((o = BuildOperation(OperationsVec->at(i))) != NULL) {
			Objects->push_back(o);
			(*ObjectMap)[o->ObjectName] = o;
		}
	}

	//after build need to set all modified flag to false
	for (std::vector<Operation*>::iterator it = OperationsVec->begin(); it != OperationsVec->end(); ++it) {
		(*it)->modified = false;
	}
}