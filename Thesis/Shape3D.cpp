#include "pch.h"
#include "Shape3D.h"
#include "GeometricOperation.h"


namespace Object {

	Shape3D::Shape3D()
	{
		GeometricType = OBJECT3D_ObjectType;
	}
	Shape3D::~Shape3D()
	{
	}

	void Shape3D::CalculateVolume()
	{
		//Zdroj: http://chenlab.ece.cornell.edu/Publication/Cha/icip01_Cha.pdf
		//v�po�et polygoni�lneho modelu je mo�n� pomocou tohoto postupu
		// - vyberie sa jeden bod v 3d priestore
		// - od ka�d�ho trojuholn�ka sa k tomuto bodu vytvor� ihlan
		// - vypocita sa objem ihlanu
		// - ak je norm�la trojuholn�ka nato�en� od bodu,
		// -	pripo��ta sa
		// -	inak sa odpo��ta 
		volume = 0;
	}

	void Shape3D::CalculateSurfaceArea()
	{

		surfaceArea = 0;
		//cycle thought mesh triangles
		//for every triangle calculate area
		for (size_t i = 0; i < 0; i++)
		{


			//get points of triangle 
			Vector3 AB = Vector3(0, 1, 0); //TODO
			Vector3 AC = Vector3(1, 0, 0);
			//calculate area

			surfaceArea += crossProduct2Vectors(AB, AC).Distance() / 2;
		}
	}

}