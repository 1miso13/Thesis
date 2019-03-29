#pragma once
#include "Vector.h"
#include <string>
#include <vector>
#include <map>
namespace Object {
	enum ObjectTypeEnum
	{
		POINT_ObjectType,
		LINE_ObjectType,
		SURFACE_ObjectType,
		CIRCLE_ObjectType,
		RECTANGLE_ObjectType,
		POLYGON_ObjectType,
		TRIANGLE_ObjectType,
		OBJECT3D_ObjectType,
		//CYLINDER_ObjectType,
		PYRAMID_ObjectType,
		SPHERE_ObjectType,
		INVALID_ObjectType
	};

	class GeometricObject
	{
	public:
		unsigned char  color[4] = {0, 0, 0, 0};
		std::string getColorHEX() {
			std::string s = "";
			for (size_t i = 0; i < 4; i++)
			{
				unsigned char a[] = { (unsigned char)(color[i] / (unsigned char)16),(unsigned char)(color[i] % (unsigned char)16) };
				for (size_t j = 0; j < 2; j++)
				{
					if (a[j] <= 9)
					{
						a[j] += '0';
					}
					else//10-15 = A-F
					{
						a[j] += 'A' - 10;
					}
					s += a[j];
				}
			}
			return s;
		}
		ObjectTypeEnum GeometricType = INVALID_ObjectType;
		std::string ObjectName;
		std::string TypeToText()
		{
			switch (GeometricType)
			{
			case POINT_ObjectType:
				return "Point";
			case LINE_ObjectType:
				return "Line";
			case SURFACE_ObjectType:
				return "Surface";
			case CIRCLE_ObjectType:
				return "Circle";
			case RECTANGLE_ObjectType:
				return "Rectangle";
			case POLYGON_ObjectType:
				return "Polygon";
			case TRIANGLE_ObjectType:
				return "Triangle";
			case OBJECT3D_ObjectType:
				return "3D object";
			case PYRAMID_ObjectType:
				return "Pyramid";
			case SPHERE_ObjectType:
				return "Sphere";
			case INVALID_ObjectType:
				return "Invalid";
			default:
				break;
			}
			return std::string();
		}
	};

}