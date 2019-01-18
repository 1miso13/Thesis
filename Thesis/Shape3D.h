#pragma once
#include "GeometricObject.h"
class Shape3D :
	public GeometricObject
{
private:
	/// <summary>
	/// After creating object call this 
	/// </summary>
	void virtual CalculateVolume();
	/// <summary>
	/// After creating object call this
	/// </summary>
	void virtual CalculateSurfaceArea();
public:
	double volume;
	double surfaceArea;
	Shape3D();
	~Shape3D();
	void virtual CreateMesh() {

	}
};

