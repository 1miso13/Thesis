#pragma once
#include "GeometricObject.h"
#include "Point.h"
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
};

