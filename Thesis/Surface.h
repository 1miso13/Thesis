#pragma once
#include "GeometricObject.h"
class Surface :
	public GeometricObject
{
public:
	short type;
	Vector3 normal;
	Vector3 center;
	Surface();
	~Surface();
	void CreateMesh();//TODO
};

