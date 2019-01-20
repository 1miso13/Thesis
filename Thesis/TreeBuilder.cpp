/// <summary>
/// TODO BUG: operations with parameter Polygon or Rectangle can't be defined in GeometricOperation
/// </summary>
#include "pch.h"
#include "TreeBuilder.h"
#include <string>
#include "Shape3D.h"
#include "Pyramid.h"
#include "Sphere.h"

/*std::vector <std::string> *CommandParameterVector = NULL;
operationType::OperationTypeEnum operationType;
float visibility = true;
std::string name;
size_t typeOfParameters;*/
void TreeBuilder::Build()
{
	//clear objects
	for (size_t i = 0; i < Objects->size(); i++)
	{
		delete Objects->at(i);
	}
	Objects->clear();


	GeometricObject * o = NULL;
	//Create new objects
	for (size_t i = 0; i < GraphCommand->size(); i++)
	{
		if ((o = BuildObject(GraphCommand->at(i))) != NULL)
			Objects->push_back(o);
	}
}

GeometricObject * TreeBuilder::FindObjectByName(std::vector<GeometricObject*>* Objects, std::string objectName)
{
	for (size_t i = 0; i < Objects->size(); i++)
	{
		if (Objects->at(i)->ObjectName == objectName)
		{
			return Objects->at(i);
		}
	}
	return nullptr;
}

//RECTANGLE BUG
Rectangle AddWidthToLineVec(Line l, float width, Line normal, short type) {
	/*type:
		0 - width/2 to left, width/2 to right
		1 - width to left
		2 - width to right
		*/
	Vector3 normalVector = normal.Vector();
	float X = (float)l.distance;
	float Y = width;
	Point center;
	Vector3 VecToEdge;
	switch (type)
	{
	case 0:
		center = Operations::LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f);
		break;
	case 1:
		VecToEdge = 0.5 * crossProduct2Vectors(l.Normal(), normalVector).Normalize();
		center = Operations::LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f) + VecToEdge;
		break;
	case 2:
		VecToEdge = 0.5 * crossProduct2Vectors(normalVector, l.Normal()).Normalize();
		center = Operations::LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f) + VecToEdge;
		break;
	default:
		break;
	}

	return Rectangle(X, Y, l.Normal(), center, normalVector);
}

//if (command->typeOfParameters == 1) {
//
//}
//else {//2
//
//}

/// <summary>
/// Return NULL if operation error
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
GeometricObject * TreeBuilder::BuildObject(Command * command)
{
	GeometricObject * RetObject=NULL;
	if (command->operationType == operationType::Point) {
		float X = std::stof(command->CommandParameterVector->at(0));
		float Y = std::stof(command->CommandParameterVector->at(1));
		float Z = std::stof(command->CommandParameterVector->at(2));
		if (command->typeOfParameters == 1) {
			RetObject = new Point(Operations::CreatePoint(X, Y, Z));
		}
		else {//2
			//find parent with that name
			Point* Parent = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(3));

			RetObject = new Point(Operations::CreatePoint(Parent, X, Y, Z));
		}
	}
	else
		if (command->operationType == operationType::LinearInterpolationDist) {
			Point* p1 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Point* p2 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));

			float distance = std::stof(command->CommandParameterVector->at(2));
			RetObject = new Point(Operations::LinearInterpolation_Distance(p1,p2,distance));
		}
	else
	if (command->operationType == operationType::LinearInterpolationPerc) {
		Point* p1 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		Point* p2 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));

		float distance = std::stof(command->CommandParameterVector->at(2));
		RetObject = new Point(Operations::LinearInterpolation_Percent(*p1, *p2, distance));
	}
	else
	if (command->operationType == operationType::Intersection_Plane_Line) {
		Line* l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		Surface* s = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
		Operations::Err err;
		Point p = Intersection_Plane_Line(s,l,&err);
		if (err == Operations::Err::Valid)
		{
			RetObject = new Point(p);
		}
	}
	else
	if (command->operationType == operationType::SurfaceCenterBoundingSquare) {
		Surface *t = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		//TODO  
		RetObject = new Point();
	}
	else
	if (command->operationType == operationType::SurfaceCenterAverage) {
		Surface *t = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		//TODO
		RetObject = new Point();
	}
	else
	if (command->operationType == operationType::Centroid) {
		Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		RetObject = new Point(Operations::Centroid(t));
	}
	else
	if (command->operationType == operationType::Incenter) {

		Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		RetObject = new Point(Operations::Incenter(t));
	}
	else
	if (command->operationType == operationType::Circumcenter) {
		Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		RetObject = new Point(Operations::Circumcenter(t));
	}
	else
	if (command->operationType == operationType::Orthocenter) {
		Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		RetObject = new Point(Operations::Orthocenter(t));
	}
	else
	if (command->operationType == operationType::NinePointCenter) {
		Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
		RetObject = new Point(Operations::NinePointCenter(t));
	}
	else
		if (command->operationType == operationType::ObjectCenterBoundingBox) {
			Shape3D *t = (Shape3D*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			//TODO
			RetObject = new Point();
	}
	else
		if (command->operationType == operationType::ObjectCenterAverage) {
			Shape3D *t = (Shape3D*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			//TODO
			RetObject = new Point();
		}
	else
		if (command->operationType == operationType::LineFirstPoint) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			RetObject = new Point(l->beginPoint);
	}
	else
		if (command->operationType == operationType::LineSecondPoint) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			RetObject = new Point(l->endPoint);
	}
	else




	///Line Commands:
			
		if (command->operationType == operationType::Line) {
			Point* p1 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Point* p2 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
			RetObject = new Line(*p1, *p2);
	}
	else
		if (command->operationType == operationType::LineNormalize) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			RetObject = new Line(l->beginPoint, Point(Operations::LinearInterpolation_Distance(&l->beginPoint, &l->endPoint, 1)));
	}
	else
		if (command->operationType == operationType::LineChangeLengthDist) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			float Dist = std::stof(command->CommandParameterVector->at(1));
			RetObject = new Line(l->beginPoint, Point(Operations::LinearInterpolation_Distance(&l->beginPoint, &l->endPoint, Dist)));
	}
	else
		if (command->operationType == operationType::LineChangeLengthPerc) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			float Perc = std::stof(command->CommandParameterVector->at(1));
			RetObject = new Line(l->beginPoint, Point(Operations::LinearInterpolation_Percent(l->beginPoint, l->endPoint, Perc)));
	}
	else
		if (command->operationType == operationType::MinLineBetweenLineAndLine) {
			Line *l1 = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Line *l2 = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(1)); 
			bool errOut = false;
			Line lOut = Operations::MinLineBetweenLineAndLine(l1, l2, &errOut);
			if (errOut)
			{
				RetObject = new Line(lOut);
			}
	}
	else
		if (command->operationType == operationType::MinLineBetweenPointAndLine) {
			Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
			RetObject = new Line(Operations::MinLineBetweenLineAndPoint(*l, *p));
	}
	else
		if (command->operationType == operationType::MinLineBetweenPointAndSurface) {
			Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Surface *s = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
			RetObject = new Line(Operations::MinLineBetweenPlaneAndPoint(*p, s));
	}
	else
		if (command->operationType == operationType::MinLine) {
			if (command->typeOfParameters = 3) {
				Line *l1 = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
				Line *l2 = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
				bool errOut = false;
				Line lOut = Operations::MinLineBetweenLineAndLine(l1, l2, &errOut);
				if (errOut)
				{
					RetObject = new Line(lOut);
				}
			}
			else
				if (command->typeOfParameters = 1) {
					Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
					Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
					RetObject = new Line(Operations::MinLineBetweenLineAndPoint(*l, *p));
				}
				else
					if (command->typeOfParameters = 2) {
						Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
						Surface *s = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
						RetObject = new Line(Operations::MinLineBetweenPlaneAndPoint(*p, s));
					}
	}
	else
		if (command->operationType == operationType::SurfaceNormal) {
			Surface *s = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			RetObject = new Line(Operations::SurfaceNormal(s));
	}
	else
		if (command->operationType == operationType::LineRelocationByPoint) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
			RetObject = new Line(Operations::LineRelocationByPoint(l, *p));
	}
	else
		if (command->operationType == operationType::CrossProduct) {
			Line *l1 = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			Line *l2 = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
			RetObject = new Line(crossProduct2Vectors(l1->Vector(),l2->Vector()));
	}
	else



///Surface Commands:
			
		if (command->operationType == operationType::RectangleFromLine) {
			Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			float width = std::stof(command->CommandParameterVector->at(1));
			short type = (short)std::stoi(command->CommandParameterVector->at(3));
			if (command->typeOfParameters = 1)
			{
				Point surfacePoint  = *(Point*)FindObjectByName(Objects, command->CommandParameterVector->at(2));
				Line normalVector = Line(crossProduct2Vectors(l->Normal(), surfacePoint - l->beginPoint).Normalize());
				RetObject = new Rectangle(AddWidthToLineVec(*l, width, normalVector, type));
			}
			else
			{
				Line *normalVector = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(2));
				RetObject = new Rectangle(AddWidthToLineVec(*l, width, *normalVector, type));
			}
	}
	else
		if (command->operationType == operationType::Circle) {
			Point center = *(Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			if (command->typeOfParameters = 1)
			{
				float radius = std::stof(command->CommandParameterVector->at(1));
				Line *normalVector = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(2));
				RetObject = new Circle(Operations::CreateCircle( center,  radius,  normalVector));
			}
			else
			{
				Point *outlinePoint = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
				Point *planePoint = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(2));
				RetObject = new Circle(Operations::CreateCircle( center, outlinePoint, planePoint, true));
			}
	}
	else
		if (command->operationType == operationType::Triangle) {
			if (command->typeOfParameters = 1)
			{
				Point *p1 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
				Point *p2 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
				Point *p3 = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(2));
				RetObject = new Triangle(*p1, *p2, *p3);
			}
			else
			{
				Line *l = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
				Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
				RetObject = new Triangle(l->beginPoint,l->endPoint,*p);
			}
	}
	else
		if (command->operationType == operationType::Rectangle) {
			Point *center = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			float height = std::stof(command->CommandParameterVector->at(1));
			float width = std::stof(command->CommandParameterVector->at(2));
			float roll = std::stof(command->CommandParameterVector->at(3));
			Line *normal = (Line*)FindObjectByName(Objects, command->CommandParameterVector->at(4));
			Vector3 planeVector = Vector3(sin(roll), cos(roll), 0);
			Plane2DTo3D(&planeVector, 1, &normal->Normal(), Vector3());

			RetObject = new Rectangle(height, width, planeVector, *center, normal->Normal());
	}
	else
		if (command->operationType == operationType::Polygon) {
			std::vector <Point> pointsVector;
			for (size_t i = 0; i < command->CommandParameterVector->size(); i++)
			{
				pointsVector.push_back(*(Point*)FindObjectByName(Objects, command->CommandParameterVector->at(i)));
			}
			RetObject = new Polygon(pointsVector);
	}
	else
		if (command->operationType == operationType::Circumscribed) {
			Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			RetObject = new Circle(Operations::InscribedTriangle(t));
	}
	else
		if (command->operationType == operationType::Inscribed) {
			Triangle *t = (Triangle*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
			RetObject = new Circle(Operations::CircumscribedTriangle(*t));
	}

///Objects Commands:
	else
		if (command->operationType == operationType::Pyramid) {
			if (command->typeOfParameters = 1)
			{
				Surface *s = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
				float height = std::stof(command->CommandParameterVector->at(1));
				RetObject = new Pyramid(height, s);
			}
			else
			{
				Surface *s = (Surface*)FindObjectByName(Objects, command->CommandParameterVector->at(0));
				Point *p = (Point*)FindObjectByName(Objects, command->CommandParameterVector->at(1));
				RetObject = new Pyramid(*p,s);
			}
	}
	else
		if (command->operationType == operationType::Extrude) {
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
	RetObject->visibility = command->visibility;
	RetObject->ObjectName = command->name;
	return RetObject;
}

