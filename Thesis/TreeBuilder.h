#pragma once
#include "Rectangle.h"
#include "GeometricOperation.h"
#include "Operation.h"
#include "Shape3D.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "Polygon.h"
#include <map>
#include <utility>
#include "Expression.h"

class TreeBuilder
{
private:
	ParamRef *paramRef;

	std::map<std::string, Operation*> *OperationMap;
	float GetNumber(std::pair <operationType::ParameterTypesEnum, void*> *pair, bool * Err) {
		
		switch (pair->first)
		{
		case operationType::ParameterTypesEnum::ParameterTypeFLOAT/* || operationType::ParameterTypesEnum::ParameterTypeEXPRESSION*/:
			return ((Expression*)pair->second)->Evaluate(ObjectMap,OperationMap , paramRef, Err);//std::stof(n);
		default:
			return 0;
		}
	}
	/// <summary>
	/// Return NULL if operation error
	/// </summary>
	/// <param name="operation"></param>
	/// <returns></returns>
	Object::GeometricObject* BuildObject(Operation* operation)
	{
		Object::GeometricObject * RetObject = NULL;
		bool Err1 = false, Err2 = false, Err3 = false;
		if (operation->operationType == operationType::Point) {
			float X = GetNumber(&operation->Parameters->at(0), &Err1);
			//float X = GetNumber(operation->OperationParametersVec->at(0), &Err);
			float Y = GetNumber(&operation->Parameters->at(1), &Err2);
			float Z = GetNumber(&operation->Parameters->at(2), &Err3);
			if (Err1 || Err2 ||Err3)
			{
				return NULL;
			}
			if (operation->typeOfParameters == 1) {
				RetObject = new Object::Point(Operations::CreatePoint(X, Y, Z));
			}
			else {//2
				//find parent with that name
				Object::Point* Parent = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(3), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::CreatePoint(Parent, X, Y, Z));
			}
		}
		else
			if (operation->operationType == operationType::LinearInterpolationDist) {
				Object::Point* p1 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Point* p2 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);

				float distance = GetNumber(&operation->Parameters->at(2), &Err3); 
				if (Err1 || Err2 || Err3)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::LinearInterpolation_Distance(p1, p2, distance));
			}
		else
			if (operation->operationType == operationType::LinearInterpolationPerc) {
				Object::Point* p1 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Point* p2 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);

				float distance = GetNumber(&operation->Parameters->at(2), &Err3);
				if (Err1 || Err2 || Err3)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::LinearInterpolation_Percent(*p1, *p2, distance));
			}
		else
			if (operation->operationType == operationType::Intersection_Plane_Line) {
				Object::Line* l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Surface* s = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
				Operations::Err err;
				if (Err1 || Err2 || Err3)
				{
					return NULL;
				}
				RetObject = new Object::Point(Intersection_Plane_Line(s, l, &err));
				if (err != Operations::Err::Valid)
				{
					return NULL;
				}
			}
		else
			if (operation->operationType == operationType::SurfaceCenterBoundingSquare) {
				Object::Surface *t = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);

				if (Err1)
				{
					return NULL;
				}
				//TODO  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				RetObject = new Object::Point();
			}
			else
				if (operation->operationType == operationType::SurfaceCenterAverage) {
					Object::Surface *t = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					if (Err1)
					{
						return NULL;
					}
					//TODO//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					RetObject = new Object::Point();
				}
		else
			if (operation->operationType == operationType::Centroid) {
				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::Centroid(t));
			}
		else
			if (operation->operationType == operationType::Incenter) {

				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::Incenter(t));
			}
		else
			if (operation->operationType == operationType::Circumcenter) {
				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::Circumcenter(t));
			}
		else
			if (operation->operationType == operationType::Orthocenter) {
				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::Orthocenter(t));
			}
		else
			if (operation->operationType == operationType::NinePointCenter) {
				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(Operations::NinePointCenter(t));
			}
		else
			if (operation->operationType == operationType::ObjectCenterBoundingBox) {
				Object::Shape3D *t = (Object::Shape3D*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				//TODO////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				RetObject = new Object::Point();
			}
		else
			if (operation->operationType == operationType::ObjectCenterAverage) {
				Object::Shape3D *t = (Object::Shape3D*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				//TODO////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				RetObject = new Object::Point();
			}
		else
			if (operation->operationType == operationType::LineFirstPoint) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(l->beginPoint);
			}
		else
			if (operation->operationType == operationType::LineSecondPoint) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Point(l->endPoint);
			}
		else




																	///Line Commands:

			if (operation->operationType == operationType::Line) {
			Object::Point* p1 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
			Object::Point* p2 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
			if (Err1 || Err2)
			{
				return NULL;
			}
			RetObject = new Object::Line(*p1, *p2);
		}
		else
			if (operation->operationType == operationType::LineNormalize) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Line(l->beginPoint, Object::Point(Operations::LinearInterpolation_Distance(&l->beginPoint, &l->endPoint, 1)));
			}
		else
			if (operation->operationType == operationType::LineChangeLengthDist) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				float Dist = GetNumber(&operation->Parameters->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				RetObject = new Object::Line(l->beginPoint, Object::Point(Operations::LinearInterpolation_Distance(&l->beginPoint, &l->endPoint, Dist)));
			}
		else
			if (operation->operationType == operationType::LineChangeLengthPerc) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				float Perc = GetNumber(&operation->Parameters->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				RetObject = new Object::Line(l->beginPoint, Object::Point(Operations::LinearInterpolation_Percent(l->beginPoint, l->endPoint, Perc)));
			}
		else
			if (operation->operationType == operationType::MinLineBetweenLineAndLine) {
				Object::Line *l1 = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Line *l2 = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				bool errOut = false;
				Object::Line lOut = Operations::MinLineBetweenLineAndLine(l1, l2, &errOut);
				if (errOut)
				{
					RetObject = new Object::Line(lOut);
				}
				else
				{
					return NULL;
				}
			}
		else
			if (operation->operationType == operationType::MinLineBetweenPointAndLine) {
				Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				RetObject = new Object::Line(Operations::MinLineBetweenLineAndPoint(*l, *p));
			}
		else
			if (operation->operationType == operationType::MinLineBetweenPointAndSurface) {
				Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				RetObject = new Object::Line(Operations::MinLineBetweenPlaneAndPoint(*p, s));
			}
		else
			if (operation->operationType == operationType::MinLine) {
				if (operation->typeOfParameters == 3) {
					Object::Line *l1 = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					Object::Line *l2 = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
					if (Err1 || Err2)
					{
						return NULL;
					}
					bool errOut = false;
					Object::Line lOut = Operations::MinLineBetweenLineAndLine(l1, l2, &errOut);
					if (errOut)
					{
						RetObject = new Object::Line(lOut);
					}
					else
					{
						return NULL;
					}
				}
				else
					if (operation->typeOfParameters == 1) {
						Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
						Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
						if (Err1 || Err2)
						{
							return NULL;
						}
						RetObject = new Object::Line(Operations::MinLineBetweenLineAndPoint(*l, *p));
					}
					else
						if (operation->typeOfParameters == 2) {
							Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
							Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
							if (Err1 || Err2)
							{
								return NULL;
							}
							RetObject = new Object::Line(Operations::MinLineBetweenPlaneAndPoint(*p, s));
						}
			}
		else
			if (operation->operationType == operationType::SurfaceNormal) {
				Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Line(Operations::SurfaceNormal(s));
			}
		else
			if (operation->operationType == operationType::LineRelocationByPoint) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				RetObject = new Object::Line(Operations::LineRelocationByPoint(l, *p));
			}
		else
			if (operation->operationType == operationType::CrossProduct) {
				Object::Line *l1 = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				Object::Line *l2 = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				RetObject = new Object::Line(crossProduct2Vectors(l1->Vector(), l2->Vector()));
			}
		else



		///Surface Commands:

			if (operation->operationType == operationType::RectangleFromLine) {
				Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				float width = GetNumber(&operation->Parameters->at(1), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				short type = (short)std::stoi(operation->OperationParametersVec->at(3));
				if (operation->typeOfParameters == 1)
				{
					Object::Point* surfacePoint = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(2), &Err1);
					if (Err1)
					{
						return NULL;
					}
					Object::Line normalVector = Object::Line(crossProduct2Vectors(l->Normal(), *surfacePoint - l->beginPoint).Normalize());
					RetObject = Operations::AddWidthToLineVec(*l, width, normalVector, type);
				}
				else
				{
					Object::Line *normalVector = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(2), &Err1);
					if (Err1)
					{
						return NULL;
					}
					RetObject = Operations::AddWidthToLineVec(*l, width, *normalVector, type);
				}
			}
		else
			if (operation->operationType == operationType::Circle) {
				Object::Point* center = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (operation->typeOfParameters == 1)
				{
					float radius = GetNumber(&operation->Parameters->at(1), &Err2);
					Object::Line *normalVector = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(2), &Err3);
					if (Err1 || Err2 || Err3)
					{
						return NULL;
					}
					RetObject = new Object::Circle(Operations::CreateCircle(*center, radius, normalVector));
				}
				else
				{
					Object::Point *outlinePoint = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err1);
					Object::Point *planePoint = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(2), &Err2);
					if (Err1 || Err2)
					{
						return NULL;
					}
					RetObject = new Object::Circle(Operations::CreateCircle(*center, outlinePoint, planePoint, true));
				}
			}
		else
			if (operation->operationType == operationType::Triangle) {
				if (operation->typeOfParameters == 1)
				{
					Object::Point *p1 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					Object::Point *p2 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
					Object::Point *p3 = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(2), &Err3);
					if (Err1 || Err2|| Err3)
					{
						return NULL;
					}
					RetObject = new Object::Triangle(*p1, *p2, *p3);
				}
				else
				{
					Object::Line *l = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
					if (Err1 || Err2)
					{
						return NULL;
					}
					RetObject = new Object::Triangle(l->beginPoint, l->endPoint, *p);
				}
			}
		else
			if (operation->operationType == operationType::Rectangle) {
				Object::Point *center = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				float height = GetNumber(&operation->Parameters->at(1), &Err2);
				float width = GetNumber(&operation->Parameters->at(2), &Err3);

				if (Err1 || Err2 || Err3)
				{
					return NULL;
				}
				float roll = GetNumber(&operation->Parameters->at(3), &Err1);
				
				Object::Line *normal = (Object::Line*)FindObjectByName(Objects, operation->OperationParametersVec->at(4), &Err2);
				if (Err1 || Err2)
				{
					return NULL;
				}
				Vector3 planeVector = Vector3(sin(roll), cos(roll), 0);
				Plane2DTo3D(&planeVector, 1, &normal->Normal(), Vector3());

				RetObject = new Object::Rectangle(height, width, planeVector, *center, normal->Normal());
				
			}
		else
			if (operation->operationType == operationType::Polygon) {
				std::vector <Object::Point> pointsVector;
				for (size_t i = 0; i < operation->OperationParametersVec->size(); i++)
				{
					auto a = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(i), &Err1);
					if (!Err1)
					{
						pointsVector.push_back(*a);
					}
				}
				if (pointsVector.size() < 3)
				{
					return NULL;
				}
				RetObject = new Object::Polygon(pointsVector);
			}
		else
			if (operation->operationType == operationType::Circumscribed) {
				Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
				if (Err1)
				{
					return NULL;
				}
				RetObject = new Object::Circle(Operations::InscribedTriangle(t));
			}
			else
				if (operation->operationType == operationType::Inscribed) {
					Object::Triangle *t = (Object::Triangle*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					if (Err1)
					{
						return NULL;
					}
					RetObject = new Object::Circle(Operations::CircumscribedTriangle(*t));
				}

		///Objects Commands:
		else
			if (operation->operationType == operationType::Sphere) {
				//TODO NOT IMPLEMENTED
				// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		else
			if (operation->operationType == operationType::Pyramid) {
				if (operation->typeOfParameters == 1)
				{
					Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					float height = GetNumber(&operation->Parameters->at(1), &Err2);
					if (Err1 || Err2)
					{
						return NULL;
					}
					RetObject = new Object::Pyramid(height, s);
				}
				else
				{
					Object::Surface *s = (Object::Surface*)FindObjectByName(Objects, operation->OperationParametersVec->at(0), &Err1);
					Object::Point *p = (Object::Point*)FindObjectByName(Objects, operation->OperationParametersVec->at(1), &Err2);
					if (Err1 || Err2)
					{
						return NULL;
					}
					RetObject = new Object::Pyramid(*p, s);
				}
			}
		else
			if (operation->operationType == operationType::Extrude) {
				//TODO NOT IMPLEMENTED

			}
		else
			if (operation->operationType == operationType::BooleanUnion) {
				//TODO NOT IMPLEMENTED
			}
		else
			if (operation->operationType == operationType::BooleanIntersection) {
				//TODO NOT IMPLEMENTED

			}
		else
			if (operation->operationType == operationType::BooleanNOT) {
				//TODO NOT IMPLEMENTED

		}
		//else
		//	if (operation->operationType == operationType::SpericalCurvedSurface) {
		//		//NOT IMPLEMENTED
		//}
		//else
		//	if (operation->operationType == operationType::Cylinder) {
		//		//NOT IMPLEMENTED
		//	}
		if (RetObject != NULL)
		{
			RetObject->color[0] = operation->color[0];
			RetObject->color[1] = operation->color[1];
			RetObject->color[2] = operation->color[2];
			RetObject->color[3] = operation->color[3];
			RetObject->ObjectName = operation->name;
		}
		return RetObject;
	}
	std::map<std::string, Object::GeometricObject*> *ObjectMap;

public:
	TreeBuilder(std::vector <Operation*> *GraphCommandPtr,
		std::vector <Object::GeometricObject*> *ObjectsPtr,
		std::map<std::string, Object::GeometricObject*> *ObjectMapPtr,
		ParamRef *paramRef,
		std::map<std::string, Operation*>* OperationMap) {
		this->OperationsVec = GraphCommandPtr;
		this->Objects = ObjectsPtr;
		this->ObjectMap = ObjectMapPtr;
		this->paramRef = paramRef;
		this->OperationMap = OperationMap;
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
	[[deprecated]]
	void BuildOperation(Operation* operationPtr) {

	}
	Object::GeometricObject* FindObjectByName(std::vector <Object::GeometricObject*> *Objects,std::string objectName, bool *Err)
	{
		/*for (size_t i = 0; i < Objects->size(); i++)
		{
			if (Objects->at(i)->ObjectName == objectName)
			{
				return Objects->at(i);
			}
		}
		return nullptr;*/
		Object::GeometricObject* objectPtr = (*ObjectMap)[objectName];
		*Err = objectPtr == NULL;
		return objectPtr;
	}
};

