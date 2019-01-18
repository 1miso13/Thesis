#pragma once
enum ObjectTypeEnum
{
	POINTObjectType,
	LINE,
	SURFACE,
	CIRCLE,
	RECTANGLE,
	POLYGON,
	TRIANGLE,
	PYRAMID,
	OBJECT3D,
	CYLINDER,
	PYRAMID,
	SPHERE,
	INVALIDObjectType
};

class GeometricObject
{
public:
	ObjectTypeEnum GeometricType;
	std::string ObjectName;
};
