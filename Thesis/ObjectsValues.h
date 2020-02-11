#pragma once
#include "GeometricObject.h"
#include "Point.h"

/// <summary>
/// 0D
/// </summary>
#include "Point.h"
/// <summary>
/// 1D
/// </summary>
#include "Line.h"
/// <summary>
/// 2D
/// </summary>
#include "Surface.h"
#include "Circle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Triangle.h"
/// <summary>
/// 3D
/// </summary>
#include "Shape3D.h"
#include "Pyramid.h"
#include "Sphere.h"
class ObjectsValues
{
public:
	static std::vector<Object::ObjectTypeEnum>  getObjectValues_lists(Object::ObjectTypeEnum type, std::vector<std::string>* ObjectValues_Options) {
		switch (type) {

		case Object::ObjectTypeEnum::POINT_ObjectType:
			*ObjectValues_Options = { "X","Y","Z" };
			return { Object::INVALID_ObjectType,Object::INVALID_ObjectType,Object::INVALID_ObjectType };
			break;
		case Object::ObjectTypeEnum::LINE_ObjectType:
			*ObjectValues_Options = { "beginPoint", "endPoint", "length", "middle" };
			return { Object::POINT_ObjectType,Object::POINT_ObjectType,Object::INVALID_ObjectType,Object::POINT_ObjectType };
			break;
		case Object::ObjectTypeEnum::SURFACE_ObjectType:
			*ObjectValues_Options = {
			"perimeter",
			"area",
			"center" };
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType };
		case Object::ObjectTypeEnum::CIRCLE_ObjectType:
			*ObjectValues_Options = {
			"perimeter",
			"area",
			"center",
			"radius"};
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType};
		case Object::ObjectTypeEnum::RECTANGLE_ObjectType:  
			*ObjectValues_Options = {
			"perimeter",
			"area",
			"center",
			"sizeX",
			"sizeY"};
			return { 
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType };
		case Object::ObjectTypeEnum::POLYGON_ObjectType:
			*ObjectValues_Options = {
			"perimeter",
			"area" };
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType };
			break;
		case Object::ObjectTypeEnum::TRIANGLE_ObjectType:
			*ObjectValues_Options = {
			"perimeter",
			"area",
			"p1",
			"p2",
			"p3"};
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType };
		case Object::ObjectTypeEnum::OBJECT3D_ObjectType:
			*ObjectValues_Options = {
			"volume",
			"surfaceArea" };
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType };
		case Object::ObjectTypeEnum::SPHERE_ObjectType:
			*ObjectValues_Options = {
			"volume",
			"surfaceArea",
			"center",
			"radius"};
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType};
		case Object::ObjectTypeEnum::PYRAMID_ObjectType:
			*ObjectValues_Options = {
			"volume",
			"surfaceArea",
			"apex",
			"base",
			"height"};
			return {
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType,
				Object::ObjectTypeEnum::POINT_ObjectType,
				Object::ObjectTypeEnum::SURFACE_ObjectType,
				Object::ObjectTypeEnum::INVALID_ObjectType};
		default:
			*ObjectValues_Options = {};
			return {};

		}
	}

	static double GetObjectValue(std::map<std::string, Object::GeometricObject*> *ObjectMap, std::string token, bool * Err);
};
/// <summary>
/// Get value from object 
/// </summary>
/// <param name="ObjectMap">ObjectMap</param>
/// <param name="token"></param>
/// <param name="Err"></param>
/// <returns></returns>
inline double ObjectsValues::GetObjectValue(std::map<std::string, Object::GeometricObject*>* ObjectMap, std::string token, bool * Err)
{
	*Err = false;
	///Parse by dots
	std::vector <std::string> tokenVec;
	size_t pos = 0;
	std::string tokenParser;
	while ((pos = token.find('.')) != std::string::npos) {
		tokenParser = token.substr(0, pos);
		tokenVec.push_back(tokenParser);
		token.erase(0, pos + 1);
	}
	tokenVec.push_back(token);

	Object::GeometricObject* objectPtr = (*ObjectMap)[tokenVec[0]];
	if (objectPtr == NULL)
	{
		*Err = true;
		return 0;
	}

	double value=0;
	///find
	Object::ObjectTypeEnum type = objectPtr->GeometricType;

	//Object::GeometricObject* lastChildPtr;
	Object::GeometricObject lastChild;///NEED TO TEST;
	Object::GeometricObject lastChildPoint;
	Object::GeometricObject lastChildPlane;

	std::string valueName = tokenVec.at(tokenVec.size() - 1);
	tokenVec.pop_back();

	for (size_t i = 1; (int)i < (int)(tokenVec.size())-2; i++)
	{
		switch (type) {

		case Object::ObjectTypeEnum::POINT_ObjectType: 
			break;
		case Object::ObjectTypeEnum::LINE_ObjectType:
			if (tokenVec[i] == "beginPoint")//Object::POINT_ObjectType 
			{
				lastChild = ((Object::Line*)objectPtr)->beginPoint;
			}
			else
			if (tokenVec[i] == "endPoint")//Object::POINT_ObjectType 
			{
				lastChild = ((Object::Line*)objectPtr)->beginPoint;
			}
			else
			if (tokenVec[i] == "middle")//Object::POINT_ObjectType 
			{
				lastChild = (Object::Point)((Object::Line*)objectPtr)->Middle();
			}
			else
			{
				*Err = true;
			}
			break;
		case Object::ObjectTypeEnum::SURFACE_ObjectType:
			if (tokenVec[i] == "center")//Object::ObjectTypeEnum::POINT_ObjectType
			{
				lastChild = ((Object::Surface*)objectPtr)->center;
			}
			else
			{
				*Err = true;
			}
		case Object::ObjectTypeEnum::CIRCLE_ObjectType:
			if (tokenVec[i] == "center")//Object::ObjectTypeEnum::POINT_ObjectType
			{
				lastChild = ((Object::Circle*)objectPtr)->center;
			}
			else
			{
				*Err = true;
			}
				
		case Object::ObjectTypeEnum::RECTANGLE_ObjectType:
			if (tokenVec[i] == "center")//Object::ObjectTypeEnum::POINT_ObjectType,
			{
				lastChild = ((Object::Rectangle*)objectPtr)->center;
			}
		case Object::ObjectTypeEnum::POLYGON_ObjectType:
		
				*Err = true;
				return 0;
			break;
		case Object::ObjectTypeEnum::TRIANGLE_ObjectType:
			if (tokenVec[i] == "p1")//Object::ObjectTypeEnum::POINT_ObjectType
			{
				lastChild = ((Object::Triangle*)objectPtr)->p1;
			}
			else
			if (tokenVec[i] == "p2")//Object::ObjectTypeEnum::POINT_ObjectType
			{
				lastChild = ((Object::Triangle*)objectPtr)->p2;
			}
			else
			if (tokenVec[i] == "p3")//Object::ObjectTypeEnum::POINT_ObjectType,
			{

				lastChild = ((Object::Triangle*)objectPtr)->p3;
			}
		case Object::ObjectTypeEnum::OBJECT3D_ObjectType:
			*Err = true;
			return 0;
		case Object::ObjectTypeEnum::SPHERE_ObjectType:
			if (tokenVec[i] == "center")//Object::ObjectTypeEnum::POINT_ObjectType,
			{
				lastChild = ((Object::Sphere*)objectPtr)->center;
			}
			else
			{
				*Err = true;
			}
		case Object::ObjectTypeEnum::PYRAMID_ObjectType:
			if (tokenVec[i] == "apex")//Object::ObjectTypeEnum::POINT_ObjectType,
			{
				lastChild = ((Object::Pyramid*)objectPtr)->apex;
			}
			else
				if (tokenVec[i] == "base")//Object::ObjectTypeEnum::SURFACE_ObjectType
			{
					lastChild = *((Object::Pyramid*)objectPtr)->base;
			}
				else
				{
					*Err = true;
				}
		default:
			break;

		}
		objectPtr = &lastChild;
		type = objectPtr->GeometricType;
	}


	switch (objectPtr->GeometricType)
	{
	case Object::ObjectTypeEnum::POINT_ObjectType:
		if (valueName == "X")
		{
			value = ((Object::Point*)objectPtr)->Position.X;
		}
		else
			if (valueName == "Y")
			{
				value = ((Object::Point*)objectPtr)->Position.Y;
			}
			else
				if (valueName == "Z")
				{
					value = ((Object::Point*)objectPtr)->Position.Z;
				}
				else
				{
					*Err = true;
				}
		break;
	case Object::ObjectTypeEnum::LINE_ObjectType:
		if (valueName == "length")
		{

			value = ((Object::Line*)objectPtr)->Distance();
		}
		else
		{
			*Err = true;
		}
		break;
	case Object::ObjectTypeEnum::SURFACE_ObjectType:
		if (valueName == "perimeter")
		{
			value = ((Object::Surface*)objectPtr)->GetPerimeter();
		}
		else
			if (valueName == "area")
		{
				value = ((Object::Surface*)objectPtr)->GetArea();
		}
		else
		{
			*Err = true;
		}
	case Object::ObjectTypeEnum::CIRCLE_ObjectType:
		if (valueName == "perimeter")
		{
			value = ((Object::Circle*)objectPtr)->GetPerimeter();
		}
		else
			if (valueName == "area")
			{
				value = ((Object::Circle*)objectPtr)->GetArea();
			}
		else
			if (valueName == "radius")
		{
				value = ((Object::Circle*)objectPtr)->radius;
		}
		else
		{
			*Err = true;
		}
	case Object::ObjectTypeEnum::RECTANGLE_ObjectType:
		if (valueName == "perimeter")
		{
			value = ((Object::Rectangle*)objectPtr)->GetPerimeter();
		}
		else
			if (valueName == "area")
		{
			value = ((Object::Rectangle*)objectPtr)->GetArea();
		}
		else
			if (valueName == "height")
		{
				value = ((Object::Rectangle*)objectPtr)->height;
		}
		else
			if (valueName == "width")
		{
				value = ((Object::Rectangle*)objectPtr)->width;
		}
		else
		{
			*Err = true;
		}
	case Object::ObjectTypeEnum::POLYGON_ObjectType:
		if (valueName == "perimeter")
		{
			value = ((Object::Polygon*)objectPtr)->GetPerimeter();
		}
		else
			if (valueName == "area")
		{
			value = ((Object::Polygon*)objectPtr)->GetArea();
		}
		else
		{
			*Err = true;
		}break;
	case Object::ObjectTypeEnum::TRIANGLE_ObjectType:
		if (valueName == "perimeter")
		{
			value = ((Object::Triangle*)objectPtr)->GetPerimeter();
		}
		else
			if (valueName == "area")
		{
			value = ((Object::Triangle*)objectPtr)->GetArea();
		}
		else
		{
			*Err = true;
		}
	case Object::ObjectTypeEnum::OBJECT3D_ObjectType:
		if (valueName == "volume")
		{
			value = ((Object::Shape3D*)objectPtr)->GetVolume();
		}
		else
			if (valueName == "surfaceArea")
		{
				value = ((Object::Shape3D*)objectPtr)->GetSurfaceArea();
		}
		else
		{
			*Err = true;
		}
	case Object::ObjectTypeEnum::SPHERE_ObjectType:
		if (valueName == "volume")
		{
			value = ((Object::Sphere*)objectPtr)->GetVolume();
		}
		else
			if (valueName == "surfaceArea")
			{
				value = ((Object::Sphere*)objectPtr)->GetSurfaceArea();
			}
			else
				if (valueName == "radius")
		{
					value = ((Object::Sphere*)objectPtr)->radius;
		}
		else
		{
			*Err = true;
		}
	case Object::ObjectTypeEnum::PYRAMID_ObjectType:
		if (valueName == "volume")
		{
			value = ((Object::Pyramid*)objectPtr)->GetVolume();
		}
		else
			if (valueName == "surfaceArea")
		{
				value = ((Object::Pyramid*)objectPtr)->GetSurfaceArea();
		}
		else
			if (valueName == "height")
		{
				value = ((Object::Pyramid*)objectPtr)->height;
		}
		else
		{
			*Err = true;
		}
	default:
		*Err = true;
		return 0;
		break;
	}

	return value;
}