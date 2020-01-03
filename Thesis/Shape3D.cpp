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
		//výpoèet polygoniálneho modelu je možný pomocou tohoto postupu
		// - vyberie sa jeden bod v 3d priestore
		// - od každého trojuholníka sa k tomuto bodu vytvorí ihlan
		// - vypocita sa objem ihlanu
		// - ak je normála trojuholníka natoèená od bodu,
		// -	pripoèíta sa
		// -	inak sa odpoèíta 

		volume = 0;
		Point apex(0,0,0);
		

		for (size_t i = 0; i < this->indices.size(); i+=3)
		{
			Point p1(
				this->vertices[this->indices[i] + 0],
				this->vertices[this->indices[i] + 1],
				this->vertices[this->indices[i] + 2]);
			Point p2(
				this->vertices[this->indices[i+1] + 0],
				this->vertices[this->indices[i+1] + 1],
				this->vertices[this->indices[i+1] + 2]);
			Point p3(
				this->vertices[this->indices[i+2] + 0],
				this->vertices[this->indices[i+2] + 1],
				this->vertices[this->indices[i+2] + 2]);

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
		for (int i = 0; i < this->indices.size(); i+=3)
		{
			//get points of triangle 
			Vector3 A = Vector3(
				this->vertices[this->indices[i + 0] * 3 + 0],
				this->vertices[this->indices[i + 0] * 3 + 1],
				this->vertices[this->indices[i + 0] * 3 + 2]);
			Vector3 B = Vector3(
				this->vertices[this->indices[i + 1] * 3 + 0],
				this->vertices[this->indices[i + 1] * 3 + 1],
				this->vertices[this->indices[i + 1] * 3 + 2]);
			Vector3 C = Vector3(
				this->vertices[this->indices[i + 2] * 3 + 0],
				this->vertices[this->indices[i + 2] * 3 + 1],
				this->vertices[this->indices[i + 2] * 3 + 2]);
			Vector3 AB = B - A;
			Vector3 AC = C - A;
			//calculate area
			surfaceArea += crossProduct2Vectors(AB, AC).Distance() / 2;
		}
	}

}