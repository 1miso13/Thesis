#pragma once
#include "Vector.h"
#include <string>
enum ObjectTypeEnum
{
	POINTObjectType,
	LINE,
	SURFACE,
	CIRCLE,
	RECTANGLE,
	POLYGON,
	TRIANGLE,
	OBJECT3D,
	CYLINDER,
	PYRAMID,
	SPHERE,
	INVALIDObjectType
};

class GeometricObject
{
public:
	float visibility=0;
	ObjectTypeEnum GeometricType = INVALIDObjectType;
	std::string ObjectName;
};
