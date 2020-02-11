#include "pch.h"
#include "Shape3D.h"
#include "GeometricOperation.h"
#include "Pyramid.h"

namespace Object {

	Shape3D::Shape3D()
	{
		GeometricType = OBJECT3D_ObjectType;
	}

	void Shape3D::CalculateVolume()
	{
		//Zdroj: http://chenlab.ece.cornell.edu/Publication/Cha/icip01_Cha.pdf TODO
		//v�po�et polygoni�lneho modelu je mo�n� pomocou tohoto postupu
		// - vyberie sa jeden bod v 3d priestore
		// - od ka�d�ho trojuholn�ka sa k tomuto bodu vytvor� ihlan
		// - vypocita sa objem ihlanu
		// - ak je norm�la trojuholn�ka nato�en� od bodu,
		// -	pripo��ta sa
		// -	inak sa odpo��ta 

		volume = 0;
		Point apex(0,0,0);
		

		for (size_t i = 0; i < this->indices.size(); i+=3)
		{
			Point p1(
				this->vertices[(size_t)(this->indices[i] + 0)],
				this->vertices[(size_t)(this->indices[i] + 1)],
				this->vertices[(size_t)(this->indices[i] + 2)]);
			Point p2(
				this->vertices[(size_t)(this->indices[i+1] + 0)],
				this->vertices[(size_t)(this->indices[i+1] + 1)],
				this->vertices[(size_t)(this->indices[i+1] + 2)]);
			Point p3(
				this->vertices[(size_t)(this->indices[i+2] + 0)],
				this->vertices[(size_t)(this->indices[i+2] + 1)],
				this->vertices[(size_t)(this->indices[i+2] + 2)]);

			Triangle *basePtr = new Triangle(
				p1,
				p2,
				p3);
			Pyramid p(apex, basePtr);
			p.CalculateVolume();
			if (DotProduct(basePtr->normal- p1.GetPosition(),apex.GetPosition() - p1.GetPosition())>0)
			{
				volume += p.volume;
			}
			else
			{
				volume -= p.volume;
			}
		}

	}

	void Shape3D::CalculateSurfaceArea()
	{

		surfaceArea = 0;
		//cycle thought mesh triangles
		//for every triangle calculate area
		for (size_t i = 0; i < this->indices.size(); i+=3)
		{
			//get points of triangle 
			Vector3 A = Vector3(
				this->vertices[this->indices[i + (size_t)0] * (size_t)3 + (size_t)0],
				this->vertices[this->indices[i + (size_t)0] * (size_t)3 + (size_t)1],
				this->vertices[this->indices[i + (size_t)0] * (size_t)3 + (size_t)2]);
			Vector3 B = Vector3(
				this->vertices[this->indices[i + (size_t)1] * (size_t)3 + (size_t)0],
				this->vertices[this->indices[i + (size_t)1] * (size_t)3 + (size_t)1],
				this->vertices[this->indices[i + (size_t)1] * (size_t)3 + (size_t)2]);
			Vector3 C = Vector3(
				this->vertices[this->indices[i + (size_t)2] * (size_t)3 + (size_t)0],
				this->vertices[this->indices[i + (size_t)2] * (size_t)3 + (size_t)1],
				this->vertices[this->indices[i + (size_t)2] * (size_t)3 + (size_t)2]);
			Vector3 AB = B - A;
			Vector3 AC = C - A;
			//calculate area
			surfaceArea += crossProduct2Vectors(AB, AC).Distance() / 2;
		}
	}

}