#pragma once
#include "Vector.h"
#include <string>
namespace Object {
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
		//CYLINDER,
		PYRAMID,
		SPHERE,
		INVALIDObjectType
	};

	class GeometricObject
	{
	public:
		float visibility = 0;
		ObjectTypeEnum GeometricType = INVALIDObjectType;
		std::string ObjectName;
		std::string TypeToText()
		{
			switch (GeometricType)
			{
			case POINTObjectType:
				return "Point";
			case LINE:
				return "Line";
			case SURFACE:
				return "Surface";
			case CIRCLE:
				return "Circle";
			case RECTANGLE:
				return "Rectangle";
			case POLYGON:
				return "Polygon";
			case TRIANGLE:
				return "Triangle";
			case OBJECT3D:
				return "3D object";
			case PYRAMID:
				return "Pyramid";
			case SPHERE:
				return "Sphere";
			case INVALIDObjectType:
				return "Invalid";
			default:
				break;
			}
			return std::string();
		}
	};

}