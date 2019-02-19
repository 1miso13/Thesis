#pragma once
#include "Rectangle.h"
#include "GeometricOperation.h"
#include "Operation.h"
#include "Shape3D.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "Polygon.h"
#include <map>
//
//Object::Rectangle *AddWidthToLineVec(Line l, float width, Line normal, short type) {
//	/*type:
//		0 - width/2 to left, width/2 to right
//		1 - width to left
//		2 - width to right
//		*/
//	Vector3 normalVector = normal.Vector();
//	float X = (float)l.distance;
//	float Y = width;
//	Point center;
//	Vector3 VecToEdge;
//	switch (type)
//	{
//	case 0:
//		center = Operations::LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f);
//		break;
//	case 1:
//		VecToEdge = 0.5 * crossProduct2Vectors(l.Normal(), normalVector).Normalize();
//		center = Operations::LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f) + VecToEdge;
//		break;
//	case 2:
//		VecToEdge = 0.5 * crossProduct2Vectors(normalVector, l.Normal()).Normalize();
//		center = Operations::LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f) + VecToEdge;
//		break;
//	default:
//		break;
//	}
//
//	return new Object::Rectangle(X, Y, l.Normal(), center, normalVector);
//}
class TreeBuilder
{
private:
	//RECTANGLE BUG
	
	/// <summary>
	/// Return NULL if operation error
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	Object::GeometricObject* BuildObject(Operation* command)
	{
		Object::GeometricObject * RetObject = NULL;
		if (command->operationType == operationType::Point) {
			float X = std::stof(command->OperationParametersVec->at(0));
			float Y = std::stof(command->OperationParametersVec->at(1));
			float Z = std::stof(command->OperationParametersVec->at(2));
			if (command->typeOfParameters == 1) {
				RetObject = new Object::Point(Operations::CreatePoint(X, Y, Z));
			}
			else {//2
				//find parent with that name
				Object::Point* Parent = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(3));

				RetObject = new Object::Point(Operations::CreatePoint(Parent, X, Y, Z));
			}
		}
		else
			if (command->operationType == operationType::LinearInterpolationDist) {
				Object::Point* p1 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				Object::Point* p2 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));

				float distance = std::stof(command->OperationParametersVec->at(2));
				RetObject = new Object::Point(Operations::LinearInterpolation_Distance(p1, p2, distance));
			}
			else
				if (command->operationType == operationType::LinearInterpolationPerc) {
					Object::Point* p1 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					Object::Point* p2 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));

					float distance = std::stof(command->OperationParametersVec->at(2));
					RetObject = new Object::Point(Operations::LinearInterpolation_Percent(*p1, *p2, distance));
				}
				else
					if (command->operationType == operationType::Intersection_Plane_Line) {
						Object::Line* l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
						Object::Surface* s = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
						Operations::Err err;
						Object::Point p = Intersection_Plane_Line(s, l, &err);
						if (err == Operations::Err::Valid)
						{
							RetObject = new Object::Point(p);
						}
					}
					else
						if (command->operationType == operationType::SurfaceCenterBoundingSquare) {
							Object::Surface *t = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
							//TODO  
							RetObject = new Object::Point();
						}
						else
							if (command->operationType == operationType::SurfaceCenterAverage) {
								Object::Surface *t = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
								//TODO
								RetObject = new Object::Point();
							}
							else
								if (command->operationType == operationType::Centroid) {
									Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
									RetObject = new Object::Point(Operations::Centroid(t));
								}
								else
									if (command->operationType == operationType::Incenter) {

										Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
										RetObject = new Object::Point(Operations::Incenter(t));
									}
									else
										if (command->operationType == operationType::Circumcenter) {
											Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
											RetObject = new Object::Point(Operations::Circumcenter(t));
										}
										else
											if (command->operationType == operationType::Orthocenter) {
												Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
												RetObject = new Object::Point(Operations::Orthocenter(t));
											}
											else
												if (command->operationType == operationType::NinePointCenter) {
													Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
													RetObject = new Object::Point(Operations::NinePointCenter(t));
												}
												else
													if (command->operationType == operationType::ObjectCenterBoundingBox) {
														Object::Shape3D *t = (Object::Shape3D*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
														//TODO
														RetObject = new Object::Point();
													}
													else
														if (command->operationType == operationType::ObjectCenterAverage) {
															Object::Shape3D *t = (Object::Shape3D*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
															//TODO
															RetObject = new Object::Point();
														}
														else
															if (command->operationType == operationType::LineFirstPoint) {
																Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
																RetObject = new Object::Point(l->beginPoint);
															}
															else
																if (command->operationType == operationType::LineSecondPoint) {
																	Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
																	RetObject = new Object::Point(l->endPoint);
																}
																else




																	///Line Commands:

		if (command->operationType == operationType::Line) {
			Object::Point* p1 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
			Object::Point* p2 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
			RetObject = new Object::Line(*p1, *p2);
		}
		else
			if (command->operationType == operationType::LineNormalize) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				RetObject = new Object::Line(l->beginPoint, Object::Point(Operations::LinearInterpolation_Distance(&l->beginPoint, &l->endPoint, 1)));
			}
		else
			if (command->operationType == operationType::LineChangeLengthDist) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				float Dist = std::stof(command->OperationParametersVec->at(1));
				RetObject = new Object::Line(l->beginPoint, Object::Point(Operations::LinearInterpolation_Distance(&l->beginPoint, &l->endPoint, Dist)));
			}
		else
			if (command->operationType == operationType::LineChangeLengthPerc) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				float Perc = std::stof(command->OperationParametersVec->at(1));
				RetObject = new Object::Line(l->beginPoint, Object::Point(Operations::LinearInterpolation_Percent(l->beginPoint, l->endPoint, Perc)));
			}
		else
			if (command->operationType == operationType::MinLineBetweenLineAndLine) {
				Object::Line *l1 = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				Object::Line *l2 = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
				bool errOut = false;
				Object::Line lOut = Operations::MinLineBetweenLineAndLine(l1, l2, &errOut);
				if (errOut)
				{
					RetObject = new Object::Line(lOut);
				}
			}
		else
			if (command->operationType == operationType::MinLineBetweenPointAndLine) {
				Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
				RetObject = new Object::Line(Operations::MinLineBetweenLineAndPoint(*l, *p));
			}
		else
			if (command->operationType == operationType::MinLineBetweenPointAndSurface) {
				Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
				RetObject = new Object::Line(Operations::MinLineBetweenPlaneAndPoint(*p, s));
			}
		else
			if (command->operationType == operationType::MinLine) {
				if (command->typeOfParameters == 3) {
					Object::Line *l1 = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					Object::Line *l2 = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
					bool errOut = false;
					Object::Line lOut = Operations::MinLineBetweenLineAndLine(l1, l2, &errOut);
					if (errOut)
					{
						RetObject = new Object::Line(lOut);
					}
				}
				else
					if (command->typeOfParameters == 1) {
						Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
						Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
						RetObject = new Object::Line(Operations::MinLineBetweenLineAndPoint(*l, *p));
					}
					else
						if (command->typeOfParameters == 2) {
							Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
							Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
							RetObject = new Object::Line(Operations::MinLineBetweenPlaneAndPoint(*p, s));
						}
			}
		else
			if (command->operationType == operationType::SurfaceNormal) {
				Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				RetObject = new Object::Line(Operations::SurfaceNormal(s));
			}
		else
			if (command->operationType == operationType::LineRelocationByPoint) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
				RetObject = new Object::Line(Operations::LineRelocationByPoint(l, *p));
			}
		else
			if (command->operationType == operationType::CrossProduct) {
				Object::Line *l1 = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				Object::Line *l2 = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
				RetObject = new Object::Line(crossProduct2Vectors(l1->Vector(), l2->Vector()));
			}
		else



		///Surface Commands:

			if (command->operationType == operationType::RectangleFromLine) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				float width = std::stof(command->OperationParametersVec->at(1));
				short type = (short)std::stoi(command->OperationParametersVec->at(3));
				if (command->typeOfParameters == 1)
				{
					Object::Point surfacePoint = *(Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(2));
					Object::Line normalVector = Object::Line(crossProduct2Vectors(l->Normal(), surfacePoint - l->beginPoint).Normalize());
					RetObject = Operations::AddWidthToLineVec(*l, width, normalVector, type);
				}
				else
				{
					Object::Line *normalVector = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(2));
					RetObject = Operations::AddWidthToLineVec(*l, width, *normalVector, type);
				}
			}
		else
			if (command->operationType == operationType::Circle) {
				Object::Point center = *(Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				if (command->typeOfParameters == 1)
				{
					float radius = std::stof(command->OperationParametersVec->at(1));
					Object::Line *normalVector = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(2));
					RetObject = new Object::Circle(Operations::CreateCircle(center, radius, normalVector));
				}
				else
				{
					Object::Point *outlinePoint = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
					Object::Point *planePoint = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(2));
					RetObject = new Object::Circle(Operations::CreateCircle(center, outlinePoint, planePoint, true));
				}
			}
		else
			if (command->operationType == operationType::Triangle) {
				if (command->typeOfParameters == 1)
				{
					Object::Point *p1 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					Object::Point *p2 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
					Object::Point *p3 = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(2));
					RetObject = new Object::Triangle(*p1, *p2, *p3);
				}
				else
				{
					Object::Line *l = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
					RetObject = new Object::Triangle(l->beginPoint, l->endPoint, *p);
				}
			}
		else
			if (command->operationType == operationType::Rectangle) {
				Object::Point *center = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				float height = std::stof(command->OperationParametersVec->at(1));
				float width = std::stof(command->OperationParametersVec->at(2));
				float roll = std::stof(command->OperationParametersVec->at(3));
				Object::Line *normal = (Object::Line*)FindObjectByName(Objects, command->OperationParametersVec->at(4));
				Vector3 planeVector = Vector3(sin(roll), cos(roll), 0);
				Plane2DTo3D(&planeVector, 1, &normal->Normal(), Vector3());

				RetObject = new Object::Rectangle(height, width, planeVector, *center, normal->Normal());
			}
		else
			if (command->operationType == operationType::Polygon) {
				std::vector <Object::Point> pointsVector;
				for (size_t i = 0; i < command->OperationParametersVec->size(); i++)
				{
					pointsVector.push_back(*(Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(i)));
				}
				RetObject = new Object::Polygon(pointsVector);
			}
		else
			if (command->operationType == operationType::Circumscribed) {
				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
				RetObject = new Object::Circle(Operations::InscribedTriangle(t));
			}
			else
				if (command->operationType == operationType::Inscribed) {
					Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					RetObject = new Object::Circle(Operations::CircumscribedTriangle(*t));
				}

		///Objects Commands:
		else
			if (command->operationType == operationType::Sphere) {
				//TODO NOT IMPLEMENTED

			}
		else
			if (command->operationType == operationType::Pyramid) {
				if (command->typeOfParameters == 1)
				{
					Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					float height = std::stof(command->OperationParametersVec->at(1));
					RetObject = new Object::Pyramid(height, s);
				}
				else
				{
					Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, command->OperationParametersVec->at(0));
					Object::Point *p = (Object::Point*)FindObjectByName(Objects, command->OperationParametersVec->at(1));
					RetObject = new Object::Pyramid(*p, s);
				}
			}
		else
			if (command->operationType == operationType::Extrude) {
				//TODO NOT IMPLEMENTED

			}
		else
			if (command->operationType == operationType::BooleanUnion) {
				//TODO NOT IMPLEMENTED
			}
		else
			if (command->operationType == operationType::BooleanIntersection) {
				//TODO NOT IMPLEMENTED

			}
		else
			if (command->operationType == operationType::BooleanNOT) {
				//TODO NOT IMPLEMENTED

		}
		//else
		//	if (command->operationType == operationType::SpericalCurvedSurface) {
		//		//NOT IMPLEMENTED
		//}
		//else
		//	if (command->operationType == operationType::Cylinder) {
		//		//NOT IMPLEMENTED
		//	}
		if (RetObject != NULL)
		{
			RetObject->visibility = command->visibility;
			RetObject->ObjectName = command->name;
		}
		return RetObject;
	}
	std::map<std::string, Object::GeometricObject*> *ObjectMap;

public:
	TreeBuilder(std::vector <Operation*> *GraphCommandPtr,
		std::vector <Object::GeometricObject*> *ObjectsPtr,
		std::map<std::string, Object::GeometricObject*> *ObjectMapPtr) {
		this->OperationsVec = GraphCommandPtr;
		this->Objects = ObjectsPtr;
		this->ObjectMap = ObjectMapPtr;
	}
	std::vector <Object::GeometricObject*> *Objects;
	std::vector <Operation*> *OperationsVec;
	void Build() {
		//clear objects
		try
		{
			/*for (size_t i = 0; i < Objects->size(); i++)
			{
				delete Objects->at(i);
			}*/
		}
		catch (...)
		{

		}

			Objects->clear();
			ObjectMap->clear();

		Object::GeometricObject * o = NULL;
		//Create new objects
		for (size_t i = 0; i < OperationsVec->size(); i++)
		{
			if ((o = BuildObject(OperationsVec->at(i))) != NULL) {
				Objects->push_back(o);
				(*ObjectMap)[o->ObjectName] = o;
			}
		}
	}
	//rebuild object and all their childs
	void BuildOperation(Operation* operationPtr) {

	}
	Object::GeometricObject* FindObjectByName(std::vector <Object::GeometricObject*> *Objects,std::string objectName)
	{
		/*for (size_t i = 0; i < Objects->size(); i++)
		{
			if (Objects->at(i)->ObjectName == objectName)
			{
				return Objects->at(i);
			}
		}
		return nullptr;*/
		return ObjectMap->at(objectName);
	}
};

