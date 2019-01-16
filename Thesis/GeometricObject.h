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
	INVALIDObjectType
};

class GeometricObject
{
public:
	std::string ObjectName;
};
