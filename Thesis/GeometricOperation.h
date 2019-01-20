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
Point CreatePoint(Point *Parent,
	float X, float Y, float Z);

Point CreatePoint(float X, float Y, float Z);

Point  LinearInterpolation_Distance(Point *p1, Point *p2, float distance);


Point  LinearInterpolation_Percent(Point p1, Point p2, float percentage);

enum Err
{
	LineParalell,
	//IntersectionOutsidePlane,
	BadLine,
	Valid
};
Point Intersection_Plane_Line(Surface *s, Line *l, Err *type);

Point Intersection_Line_Line2D(Line l1, Line l2);

//Point SurfaceMiddleRec(Rectangle *r);

Point SurfaceMiddleCir(Circle *c);

//Point SurfaceCenterBoundingSquare(Polygon *s);
//
//Point SurfaceCenter(Polygon *s);

Point Centroid(Triangle* t);
Point Incenter(Triangle* t);
Point Circumcenter(Triangle* t);
Point Orthocenter(Triangle* t);
Point NinePointCenter(Triangle* t);


Vector3 TriangleCentroid(Vector3 p1, Vector3 p2, Vector3 p3);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Operations For Lines////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


Line MinLineBetweenLineAndPoint(Line l, Point p);

Line MinLineBetweenLineAndLine(Line *l1/*p1-p2*/, Line *l2/*p3-p4*/, bool *errOut);

Line MinLineBetweenPlaneAndPoint(Point p, Surface *s);

Line SurfaceNormal(Surface* s);

Line LineRelocationByPoint(Line *l, Point p);


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Operations For Surfaces/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Triangle CreateTriangle(Point p, Line l);

Triangle CreateTriangle(Line l, Point p);

Circle CreateCircle(Point center, float radius, Line *lineNormal);

Circle CreateCircle(Point center, Point *outlinePoint, Point *planePoint, bool allThreePointsInsideCircle);

//Rectangle CreateRectangle(Point center, float X, float Y, float Roll/*[0,360]*/, Line normalLine);

//Polygon CreatePolygon(std::vector <Point> pointsVector);
//
//Rectangle AddWidthToLineVec(Line l, float width, Vector3 normalVector, short type);
//
//Rectangle AddWidthToLinePoint(Line l, float width, Point surfacePoint, short type);

Line PerpendicularLineOnPoint(Point origin, Point p1, Point p2);

Circle CircumscribedTriangle(Triangle triangle);

Circle InscribedTriangle(Triangle *triangle);
}