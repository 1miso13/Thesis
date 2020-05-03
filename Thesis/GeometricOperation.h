#pragma once
#include "Point.h"
#include "Geometry.h"
#include "Line.h"
#include "Surface.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Polygon.h"
//class GeometricOperation
//{
//public:
//	GeometricOperation();
//	~GeometricOperation();
//	virtual GeometricObject Action();
//private:
//
//};
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////Operations For Points///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
namespace Operations{
	Object::Point CreatePoint(Object::Point *Parent,
	float X, float Y, float Z);

	Object::Point CreatePoint(float X, float Y, float Z);

	Object::Point  LinearInterpolation_Distance(Object::Point *p1, Object::Point *p2, float distance);


	Object::Point  LinearInterpolation_Percent(Object::Point p1, Object::Point p2, float percentage);

enum Err
{
	Valid,
	LineParalell,
	//IntersectionOutsidePlane,
	BadLine
};
Object::Point Intersection_Plane_Line(Object::Surface *s, Object::Line *l, Err *type);

Object::Point Intersection_Line_Line2D(Object::Line l1, Object::Line l2);

//Point SurfaceMiddleRec(Rectangle *r);

Object::Point SurfaceMiddleCir(Object::Circle *c);

//Point SurfaceCenterBoundingSquare(Polygon *s);
//
//Point SurfaceCenter(Polygon *s);

Object::Point Centroid(Object::Triangle* t);
Object::Point Incenter(Object::Triangle* t);
Object::Point Circumcenter(Object::Triangle* t);
Object::Point* Orthocenter(Object::Triangle* t);
Object::Point NinePointCenter(Object::Triangle* t);


Vector3 TriangleCentroid(Vector3 p1, Vector3 p2, Vector3 p3);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Operations For Lines////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


Object::Line MinLineBetweenLineAndPoint(Object::Line l, Object::Point p);

Object::Line MinLineBetweenLineAndLine(Object::Line *l1/*p1-p2*/, Object::Line *l2/*p3-p4*/, bool *errOut);

Object::Line MinLineBetweenPlaneAndPoint(Object::Point p, Object::Surface *s);

Object::Line SurfaceNormal(Object::Surface* s);

Object::Line LineRelocationByPoint(Object::Line *l, Object::Point p);


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Operations For Surfaces/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object::Triangle CreateTriangle(Object::Point p, Object::Line l);

Object::Triangle CreateTriangle(Object::Line l, Object::Point p);

Object::Circle CreateCircle(Object::Point center, float radius, Object::Line *lineNormal);

Object::Circle CreateCircle(Object::Point center, Object::Point *outlinePoint, Object::Point *planePoint, bool allThreePointsInsideCircle);

//Rectangle CreateRectangle(Point center, float X, float Y, float Roll/*[0,360]*/, Line normalLine);

//Polygon CreatePolygon(std::vector <Point> pointsVector);
//
Object::Rectangle AddWidthToLineVec(Object::Line l, float width, Vector3 normalVector, short type);
//
Object::Rectangle AddWidthToLinePoint(Object::Line l, float width, Object::Point surfacePoint, short type);

Object::Line PerpendicularLineOnPoint(Object::Point origin, Object::Point p1, Object::Point p2);

Object::Circle CircumscribedTriangle(Object::Triangle triangle);

Object::Circle InscribedTriangle(Object::Triangle *triangle);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Operations For Points///////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Relative
	inline Object::Point CreatePoint(Object::Point *Parent,
		float X, float Y, float Z) {
		X = Parent->Position.X + X;
		Y = Parent->Position.Y + Y;
		Z = Parent->Position.Z + Z;
		return Object::Point(X, Y, Z);
	}
	//Absolut
	inline Object::Point CreatePoint(float X, float Y, float Z) {
		return Object::Point(X, Y, Z);
	}
	//////////////////////////////////////////////////////////
	//Calculate Interpolate from point p1 to point p2 by distance 
	inline Object::Point  LinearInterpolation_Distance(Object::Point *p1, Object::Point *p2, float distance) {
		//normalize
		Vector3 normal = (p2->Position - p1->Position).Normalize();
		Object::Point ReturnPoint = *p1 + normal * distance;
		return ReturnPoint;
	}
	//////////////////////////////////////////////////////////
	//Calculate Interpolate from point p1 to point p2 by percentage [0;1]
	inline Object::Point  LinearInterpolation_Percent(Object::Point p1, Object::Point p2, float percentage) {
		Object::Point ReturnPoint = p1 + percentage * (p2 - p1);
		return ReturnPoint;
	}

	//////////////////////////////////////////////////////////
	//Line p1 and p2 -> p1!=p2
	inline Object::Point Intersection_Plane_Line(Object::Surface *s, Object::Line *l, Err *type) {
		//need to test if intersection exists


		if (l->beginPoint.Position == l->endPoint.Position)
		{
			*type = BadLine;
			return Object::Point();
		}


		float length;
		float dotNumerator;
		float dotDenominator;
		Vector3 vector;
		Vector3 planeNormal;
		planeNormal = s->normal;
		Vector3 lineVec = (l->endPoint.Position - l->beginPoint.Position).Normalize();
		//calculate the distance between the linePoint and the line-plane intersection point
		dotNumerator = DotProduct((s->center - l->beginPoint.Position), planeNormal);
		dotDenominator = DotProduct(lineVec, planeNormal);
		Vector3 intersection = Vector3();
		//line and plane are not parallel
		if (abs(dotDenominator) > FLT_EPSILON)
		{
			length = dotNumerator / dotDenominator;

			//create a vector from the linePoint to the intersection point
			vector = length * lineVec.Normalize();

			//get the coordinates of the line-plane intersection point
			intersection = l->beginPoint.Position + vector;

			//test, if intersection is on the line
			/*if (IsOnOtherSides(planeNormal, PlanePoints[1], point1, point2) ||
				(point1.x > point2.x ?
					intersection.X <= point1.x && intersection.X >= point2.x :
					intersection.X >= point1.x && intersection.X <= point2.x)
				&&
				(point1.y > point2.y ?
					intersection.y <= point1.y && intersection.y >= point2.y :
					intersection.y >= point1.y && intersection.y <= point2.y)
				&&
				(point1.z > point2.z ?
					intersection.z <= point1.z && intersection.z >= point2.z :
					intersection.z >= point1.z && intersection.z <= point2.z)
				)
			{

			}
			else {
				*type=IntersectionOutsidePlane;
			}*/
		}
		else
		{
			*type = LineParalell;
		}

		return intersection;
	}

	//////////////////////////////////////////////////////////
	//http://paulbourke.net/geometry/pointlineplane/
	inline Object::Point Intersection_Line_Line2D(Object::Line l1, Object::Line l2) {
		float x1 = l1.beginPoint.Position.X;
		float x2 = l1.endPoint.Position.X;
		float x3 = l2.beginPoint.Position.X;
		float x4 = l2.endPoint.Position.X;

		float y1 = l1.beginPoint.Position.Y;
		float y2 = l1.endPoint.Position.Y;
		float y3 = l2.beginPoint.Position.Y;
		float y4 = l2.endPoint.Position.Y;

		//double numerator = ((double)x1 - (double)x3)*((double)y3 - (double)y4) - ((double)y1 - (double)y3)*((double)x3 - (double)x4);
		//double denominator = ((double)x1 - (double)x2)*((double)y3 - (double)y4) - ((double)y1 - (double)y2)*((double)x3 - (double)x4);
		double numerator = ((double)x4 - (double)x3)*((double)y1 - (double)y3) - ((double)y4 - (double)y3)*((double)x1 - (double)x3);
		double denominator = ((double)y4 - (double)y3)*((double)x2 - (double)x1) - ((double)x4 - (double)x3)*((double)y2 - (double)y1);

		double u = numerator / denominator;
		Vector3 v = (l1.beginPoint.Position + (u * (l1.endPoint.Position - l1.beginPoint.Position)));
		return Object::Point(v);
	}
	//////////////////////////////////////////////////////////

	inline Object::Point SurfaceMiddleRec(Object::Rectangle *r) {
		return r->center;
	}
	inline Object::Point SurfaceMiddleCir(Object::Circle *c) {
		return c->center;
	}
	inline Object::Point SurfaceMiddlePol(Object::Polygon *s) {
		//need to calculate middle
		Vector3 MinPoint = s->points.at(0).Position;
		Vector3 MaxPoint = s->points.at(0).Position;
		for (unsigned int i = 1; i < s->points.size(); i++) {
			//MAX
			if (s->points.at(i).Position.X > MaxPoint.X)
			{
				MaxPoint.X = s->points.at(i).Position.X;
			}
			if (s->points.at(i).Position.Y > MaxPoint.Y)
			{
				MaxPoint.Y = s->points.at(i).Position.Y;
			}
			if (s->points.at(i).Position.Z > MaxPoint.Z)
			{
				MaxPoint.Z = s->points.at(i).Position.Z;
			}
			//MIN
			if (s->points.at(i).Position.X < MinPoint.X)
			{
				MinPoint.X = s->points.at(i).Position.X;
			}
			if (s->points.at(i).Position.Y < MinPoint.Y)
			{
				MinPoint.Y = s->points.at(i).Position.Y;
			}
			if (s->points.at(i).Position.Z < MinPoint.Z)
			{
				MinPoint.Z = s->points.at(i).Position.Z;
			}
		}
		return (MinPoint + MaxPoint) / 2;
	}

	inline Object::Point SurfaceCenter(Object::Polygon *s) {
		//need to calculate middle
		Vector3 sumPoint;
		for (unsigned int i = 0; i < s->points.size(); i++) {
			sumPoint += s->points.at(i).Position;
		}
		return Object::Point(sumPoint / int(s->points.size()));
	}
	inline Object::Point Centroid(Object::Triangle* t) {
		return Object::Point((t->p1 + t->p2 + t->p3) / 3);
	}
	inline Object::Point Incenter(Object::Triangle* t) {
		float a = (t->p2 - t->p3).Distance();
		float b = (t->p3 - t->p1).Distance();
		float c = (t->p1 - t->p2).Distance();
		return Object::Point((a * t->p1 + b * t->p2 + c * t->p3) / (a + b + c));
	}
	inline Object::Point Circumcenter(Object::Triangle* t) {
		return CircumscribedTriangle(*t).center;
	}
	inline Object::Point* Orthocenter(Object::Triangle* t) {
		Object::Line l1 = MinLineBetweenLineAndPoint(Object::Line(t->p1, t->p2), t->p3);
		Object::Line l2 = MinLineBetweenLineAndPoint(Object::Line(t->p2, t->p3), t->p1);

		bool errOut;
		Object::Line lOut = MinLineBetweenLineAndLine(&l1/*p1-p2*/, &l2/*p3-p4*/, &errOut);
		return new Object::Point(lOut.beginPoint.Position);
	}
	inline Object::Point NinePointCenter(Object::Triangle* t) {
		Object::Triangle t2((t->p1 + t->p2) / 2,
			(t->p2 + t->p3) / 2,
			(t->p3 + t->p1) / 2);
		return CircumscribedTriangle(t2).center;
	}
	inline Vector3 TriangleCentroid(Vector3 p1, Vector3 p2, Vector3 p3) {
		return (p1 + p2 + p3) / 3;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Operations For Lines////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// http://paulbourke.net/geometry/pointlineplane/
	inline Object::Line MinLineBetweenLineAndPoint(Object::Line l, Object::Point p) {


		double u = (
			(((double)p.Position.X - (double)l.beginPoint.Position.X) * ((double)l.endPoint.Position.X - (double)l.beginPoint.Position.X)) +
			(((double)p.Position.Y - (double)l.beginPoint.Position.Y) * ((double)l.endPoint.Position.Y - (double)l.beginPoint.Position.Y)) +
			(((double)p.Position.Z - (double)l.beginPoint.Position.Z) * ((double)l.endPoint.Position.Z - (double)l.beginPoint.Position.Z))
			) / ((double)l.Distance() * (double)l.Distance());

		//TODO aj mimo ciary?
		/*if (u < 0 || u>1) {
			JE MIMO CIARY
		}*/
		float X = (float)((double)l.beginPoint.Position.X + u * ((double)l.endPoint.Position.X - (double)l.beginPoint.Position.X));
		float Y = (float)((double)l.beginPoint.Position.Y + u * ((double)l.endPoint.Position.Y - (double)l.beginPoint.Position.Y));
		float Z = (float)((double)l.beginPoint.Position.Z + u * ((double)l.endPoint.Position.Z - (double)l.beginPoint.Position.Z));

		return Object::Line(Object::Point(X, Y, Z), p);
	}
	// error if l1.dist == 0 || l2.dist == 0
	inline Object::Line MinLineBetweenLineAndLine(Object::Line *l1/*p1-p2*/, Object::Line *l2/*p3-p4*/, bool *errOut) {
		Vector3 p13, p43, p21;
		p13.X = l1->beginPoint.Position.X - l2->beginPoint.Position.X;
		p13.Y = l1->beginPoint.Position.Y - l2->beginPoint.Position.Y;
		p13.Z = l1->beginPoint.Position.Z - l2->beginPoint.Position.Z;

		//vector l2
		p43.X = l2->endPoint.Position.X - l2->beginPoint.Position.X;
		p43.Y = l2->endPoint.Position.Y - l2->beginPoint.Position.Y;
		p43.Z = l2->endPoint.Position.Z - l2->beginPoint.Position.Z;
		if (abs(p43.Distance()) < FLT_EPSILON)
		{
			*errOut = true;
			return Object::Line();
		}
		//vector l1
		p21.X = l1->endPoint.Position.X - l1->beginPoint.Position.X;
		p21.Y = l1->endPoint.Position.Y - l1->beginPoint.Position.Y;
		p21.Z = l1->endPoint.Position.Z - l1->beginPoint.Position.Z;
		if (abs(p21.Distance()) < FLT_EPSILON)
		{
			*errOut = true;
			return Object::Line();
		}


		double d1343, d4321, d1321, d4343, d2121;

		d1343 = (double)p13.X * (double)p43.X + (double)p13.Y * (double)p43.Y + (double)p13.Z * (double)p43.Z;
		d4321 = (double)p43.X * (double)p21.X + (double)p43.Y * (double)p21.Y + (double)p43.Z * (double)p21.Z;
		d1321 = (double)p13.X * (double)p21.X + (double)p13.Y * (double)p21.Y + (double)p13.Z * (double)p21.Z;
		d4343 = (double)p43.X * (double)p43.X + (double)p43.Y * (double)p43.Y + (double)p43.Z * (double)p43.Z;
		d2121 = (double)p21.X * (double)p21.X + (double)p21.Y * (double)p21.Y + (double)p21.Z * (double)p21.Z;

		double Denominator = d2121 * d4343 - d4321 * d4321;
		if (abs(Denominator) < DBL_EPSILON)
		{
			*errOut = true;
			return Object::Line();
		}
		double Numerator = d1343 * d4321 - d1321 * d4343;

		double mua = Numerator / Denominator;
		double mub = (d1343 + d4321 * (mua)) / d4343;

		Vector3 l1P, l2P;
		l1P.X = (float)(l1->beginPoint.Position.X + mua * p21.X);
		l1P.Y = (float)(l1->beginPoint.Position.Y + mua * p21.Y);
		l1P.Z = (float)(l1->beginPoint.Position.Z + mua * p21.Z);

		l2P.X = (float)(l2->beginPoint.Position.X + mub * p43.X);
		l2P.Y = (float)(l2->beginPoint.Position.Y + mub * p43.Y);
		l2P.Z = (float)(l2->beginPoint.Position.Z + mub * p43.Z);

		*errOut = false;
		return Object::Line(l1P, l2P);
	}
	inline Object::Line MinLineBetweenPlaneAndPoint(Object::Point p, Object::Surface *s) {
		//every surface have middle and normal
		double distPointToPlane = DotProduct((p.Position - s->center), s->normal);
		Object::Point p2 = p.Position - (s->normal * distPointToPlane);
		return Object::Line(p2, p);
	}
	inline Object::Line SurfaceNormal(Object::Surface* s) {
		return Object::Line(s->normal);
	}
	inline Object::Line LineRelocationByPoint(Object::Line *l, Object::Point p) {
		Object::Point diff = p - l->beginPoint;
		return Object::Line(p, l->endPoint + diff);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Operations For Surfaces/////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline Object::Triangle CreateTriangle(Object::Point p, Object::Line l) {
		return Object::Triangle(p, l.beginPoint, l.endPoint);
	}
	inline Object::Triangle CreateTriangle(Object::Line l, Object::Point p) {
		return Object::Triangle(l.beginPoint, l.endPoint, p);
	}
	//circle
	inline Object::Circle CreateCircle(Object::Point center, float radius, Object::Line *lineNormal) {

		return Object::Circle(center, radius, lineNormal->Normal());
	}
	inline Object::Circle CreateCircle(Object::Point center, Object::Point *outlinePoint, Object::Point *planePoint, bool allThreePointsInsideCircle) {

		//radius
		float radius = (*outlinePoint - center).Distance();
		if (allThreePointsInsideCircle)
		{
			float d;
			if ((d = (*planePoint - center).Distance()) > radius)
			{
				radius = d;
			}
		}

		//normal
		Vector3 arrayOfPoints[] = { center.Position, outlinePoint->Position, planePoint->Position };
		Vector3 normal = crossProduct3Points(arrayOfPoints).Normalize();

		return Object::Circle(center, radius, normal);
	}

	//rectangle
	inline Object::Rectangle CreateRectangle(Object::Point center, float height, float width, float Roll/*[0,360]*/, Object::Line normalLine) {
		Vector3 planeVector = Vector3(sin(Roll), cos(Roll), 0);
		Plane2DTo3D(&planeVector, 1, &normalLine.Normal(), Vector3());


		return Object::Rectangle(height, width, planeVector, center, normalLine.Normal());
	}

	inline Object::Polygon CreatePolygon(std::vector <Object::Point> pointsVector) { //minimum 3 points 

		return Object::Polygon(pointsVector);
	}

	//if normal vector is not perpendicular to line, as normal is used normalized dot product between line and normal vector
	//if normal vector is same direction as line normal, exception occurred
	inline Object::Rectangle AddWidthToLineVec(Object::Line l, float width, Vector3 normalVector, short type) {
		/*type:
		*	0 - width/2 to left, width/2 to right
		*	1 - width to left
		*	2 - width to right
			*/
			//TODO
		float height = (float)l.distance;
		Object::Point center;
		Vector3 VecToEdge;
		switch (type)
		{
		case 0:
			center = LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f);
			break;
		case 1:
			VecToEdge = 0.5 * crossProduct2Vectors(l.Normal(), normalVector).Normalize();
			center = LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f) + VecToEdge;
			break;
		case 2:
			VecToEdge = 0.5 * crossProduct2Vectors(normalVector, l.Normal()).Normalize();
			center = LinearInterpolation_Percent(l.beginPoint, l.endPoint, 0.5f) + VecToEdge;
			break;
		default:
			break;
		}

		return Object::Rectangle(height, width, l.Normal(), center, normalVector);
	}
	//
	inline Object::Rectangle AddWidthToLinePoint(Object::Line l, float width, Object::Point surfacePoint, short type) {
		/*type:
		*	0 - width/2 to left, width/2 to right
		*	1 - width to left
		*	2 - width to right
			*/
			//TODO
		Vector3 normalVector = crossProduct2Vectors(l.Normal(), surfacePoint - l.beginPoint).Normalize();
		return AddWidthToLineVec(l, width, normalVector, type);
	}

	inline Object::Rectangle *AddWidthToLineVec(Object::Line l, float width, Object::Line normal, short type) {
	/*type:
	*	0 - width/2 to left, width/2 to right
	*	1 - width to left
	*	2 - width to right
		*/
	Vector3 normalVector = normal.Vector();
	float X = (float)l.distance;
	float Y = width;
	Object::Point center;
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

	return new Object::Rectangle(X, Y, l.Normal(), center, normalVector);
}
	//Circumscribed
	inline Object::Line PerpendicularLineOnPoint(Object::Point origin, Object::Point p1, Object::Point p2) {
		//move line points origin to center
		Object::Point p1a = p1 - origin;
		Object::Point p2a = p2 - origin;

		//rotate
		Vector3 temp = p1a.Position;
		p1a.Position.X = -temp.Y;
		p1a.Position.Y = temp.X;

		temp = p2a.Position;
		p2a.Position.X = -temp.Y;
		p2a.Position.Y = temp.X;

		//move points back
		p1a = p1a + origin;
		p2a = p2a + origin;
		return Object::Line(p1a, p2a);
	}
	inline Object::Circle CircumscribedTriangle(Object::Triangle triangle) {
		//to 2D
		Vector3 normal;
		Vector3 arrayOfPoints[] = { triangle.p1.Position, triangle.p2.Position, triangle.p3.Position, Vector3() };
		Vector3 origin = triangle.p1.Position;
		Plane3DTo2D(arrayOfPoints, 3, &normal, origin);
		//Find center of circle
			//Find perpendicular line in middle of 2 random lines
				//	1.
		Object::Point middle01 = LinearInterpolation_Percent(arrayOfPoints[0], arrayOfPoints[1], 0.5f);
		Object::Line A = PerpendicularLineOnPoint(middle01, arrayOfPoints[0], arrayOfPoints[1]);
		//	2.
		Object::Point middle12 = LinearInterpolation_Percent(arrayOfPoints[1], arrayOfPoints[2], 0.5f);
		Object::Line B = PerpendicularLineOnPoint(middle12, arrayOfPoints[1], arrayOfPoints[2]);
		//find intersection of these lines
		arrayOfPoints[3]/*Point middle*/ = Intersection_Line_Line2D(A, B).Position;
		//find range of circle
			//distance between middle and any point
		float radius = (arrayOfPoints[3] - arrayOfPoints[0]).Distance();
		//to 3D
		Plane2DTo3D(arrayOfPoints, 4/* 3 triangle + 1 circle center*/, &normal, origin);
		//MovePlaneToBase();
		return Object::Circle(arrayOfPoints[3], radius, normal);
	}





	inline Object::Circle InscribedTriangle(Object::Triangle *triangle) {
		//to2D
		Vector3 arrayOfPoints[4] = { triangle->p1.Position, triangle->p2.Position, triangle->p3.Position, Vector3()/*center*/ };
		Vector3 normal;
		Vector3 origin = triangle->p1.Position;
		Plane3DTo2D(arrayOfPoints, 3, &normal);

		//find Line between l12 and l13 (point p1)
			//find angle/2 - bisector
		Object::Point v12 = LinearInterpolation_Distance(&triangle->p1, &triangle->p2, 1);
		Object::Point v13 = LinearInterpolation_Distance(&triangle->p1, &triangle->p3, 1);

		//point in middle
		Object::Point Middle1 = LinearInterpolation_Percent(v12, v13, 0.5f);
		//find Line between l21 and l23 (point p1)
			//find angle/2 - bisector
		Object::Point v21 = LinearInterpolation_Distance(&triangle->p2, &triangle->p1, 1);
		Object::Point v23 = LinearInterpolation_Distance(&triangle->p2, &triangle->p3, 1);

		//
		Object::Point Middle2 = LinearInterpolation_Percent(v21, v23, 0.5f);

		//find middle between vectorFromPoint2 and vectorFromPoint2

		arrayOfPoints[3] = Intersection_Line_Line2D(Object::Line(triangle->p1, Middle1), Object::Line(triangle->p2, Middle2)).Position;
		//find range of lines (all distances between middle to lines are same)

		float radius = (float)MinLineBetweenLineAndPoint(Object::Line(triangle->p1, triangle->p2), arrayOfPoints[3]).Distance();


		//to 3D
		Plane2DTo3D(arrayOfPoints, 4/* 3 triangle + 1 circle center*/, &normal, origin);
		return Object::Circle(arrayOfPoints[3], radius, normal);

	}


}
