#include <math.h>
#include "pch.h"
#include "GeometricOperation.h"


namespace Operations {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Operations For Points///////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Relative
	Point CreatePoint(Point *Parent,
		float X, float Y, float Z) {
		X = Parent->Position.X + X;
		Y = Parent->Position.Y + Y;
		Z = Parent->Position.Z + Z;
		return Point(X, Y, Z);
	}
	//Absolut
	Point CreatePoint(float X, float Y, float Z) {
		return Point(X, Y, Z);
	}
	//////////////////////////////////////////////////////////
	//Calculate Interpolate from point p1 to point p2 by distance 
	Point  LinearInterpolation_Distance(Point *p1, Point *p2, float distance) {
		//normalize
		Vector3 normal = (p2->Position - p1->Position).Normalize();
		Point ReturnPoint = *p1 + normal * distance;
		return ReturnPoint;
	}
	//////////////////////////////////////////////////////////
	//Calculate Interpolate from point p1 to point p2 by percentage [0;1]
	Point  LinearInterpolation_Percent(Point p1, Point p2, float percentage) {
		Point ReturnPoint = p1 + percentage * (p2 - p1);
		return ReturnPoint;
	}

	//////////////////////////////////////////////////////////
	//Line p1 and p2 -> p1!=p2
	Point Intersection_Plane_Line(Surface *s, Line *l, Err *type) {
		//need to test if intersection exists


		if (l->beginPoint.Position == l->endPoint.Position)
		{
			*type = BadLine;
			return Point();
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
	Point Intersection_Line_Line2D(Line l1, Line l2) {
		float x1 = l1.beginPoint.Position.X;
		float x2 = l1.endPoint.Position.X;
		float x3 = l2.beginPoint.Position.X;
		float x4 = l2.endPoint.Position.X;

		float y1 = l1.beginPoint.Position.Y;
		float y2 = l1.endPoint.Position.Y;
		float y3 = l2.beginPoint.Position.Y;
		float y4 = l2.endPoint.Position.Y;

		double numerator = ((double)x1 - (double)x3)*((double)y3 - (double)y4) - ((double)y1 - (double)y3)*((double)x3 - (double)x4);
		double denominator = ((double)x1 - (double)x2)*((double)y3 - (double)y4) - ((double)y1 - (double)y2)*((double)x3 - (double)x4);

		double u = numerator / denominator;
		Vector3 v = (l1.beginPoint.Position + (u * (l1.endPoint.Position - l1.beginPoint.Position)));
		return Point(v);
	}
	//////////////////////////////////////////////////////////

	Point SurfaceMiddleRec(Rectangle *r) {
		return r->center;
	}
	Point SurfaceMiddleCir(Circle *c) {
		return c->center;
	}
	Point SurfaceMiddlePol(Polygon *s) {
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

	Point SurfaceCenter(Polygon *s) {
		//need to calculate middle
		Vector3 sumPoint;
		for (unsigned int i = 0; i < s->points.size(); i++) {
			sumPoint += s->points.at(i).Position;
		}
		return Point(sumPoint / int(s->points.size()));
	}
	Point Centroid(Triangle* t) {
		return Point((t->p1 + t->p2 + t->p3)/3);
	}
	Point Incenter(Triangle* t) {
		float a = (t->p2 - t->p3).Distance();
		float b = (t->p3 - t->p1).Distance();
		float c = (t->p1 - t->p2).Distance();
		return Point((a * t->p1 + b * t->p2 + c * t->p3)/(a+b+c));
	}
	Point Circumcenter(Triangle* t) {
		return CircumscribedTriangle(*t).center;
	}
	Point Orthocenter(Triangle* t) {
		Line l1 = MinLineBetweenLineAndPoint(Line(t->p1,t->p2), t->p3);
		Line l2 = MinLineBetweenLineAndPoint(Line(t->p2,t->p3), t->p1);

		bool errOut;
		Line lOut = MinLineBetweenLineAndLine(&l1/*p1-p2*/, &l2/*p3-p4*/, &errOut);
		return lOut.beginPoint;;
	}
	Point NinePointCenter(Triangle* t) {
		Triangle t2((t->p1 + t->p2) / 2,
			(t->p2 + t->p3) / 2,
			(t->p3 + t->p1) / 2);
		return CircumscribedTriangle(t2).center;
	}
	Vector3 TriangleCentroid(Vector3 p1, Vector3 p2, Vector3 p3) {
		return (p1 + p2 + p3) / 3;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Operations For Lines////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// http://paulbourke.net/geometry/pointlineplane/
	Line MinLineBetweenLineAndPoint(Line l, Point p) {


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

		return Line(Point(X, Y, Z), p);
	}
	// error if l1.dist == 0 || l2.dist == 0
	Line MinLineBetweenLineAndLine(Line *l1/*p1-p2*/, Line *l2/*p3-p4*/, bool *errOut) {
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
			return Line();
		}
		//vector l1
		p21.X = l1->endPoint.Position.X - l1->beginPoint.Position.X;
		p21.Y = l1->endPoint.Position.Y - l1->beginPoint.Position.Y;
		p21.Z = l1->endPoint.Position.Z - l1->beginPoint.Position.Z;
		if (abs(p21.Distance()) < FLT_EPSILON)
		{
			*errOut = true;
			return Line();
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
			return Line();
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
		return Line(l1P, l2P);
	}
	Line MinLineBetweenPlaneAndPoint(Point p, Surface *s) {
		//every surface have middle and normal
		double distPointToPlane = DotProduct((p.Position - s->center), s->normal);
		Point p2 = p.Position - (s->normal * distPointToPlane);
		return Line(p2, p);
	}
	Line SurfaceNormal(Surface* s) {
		return Line(s->normal);
	}
	Line LineRelocationByPoint(Line *l, Point p) {
		Point diff = p - l->beginPoint;
		return Line(p, l->endPoint + diff);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Operations For Surfaces/////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Triangle CreateTriangle(Point p, Line l) {
		return Triangle(p, l.beginPoint, l.endPoint);
	}
	Triangle CreateTriangle(Line l, Point p) {
		return Triangle(l.beginPoint, l.endPoint, p);
	}
	//circle
	Circle CreateCircle(Point center, float radius, Line *lineNormal) {

		return Circle(center, radius, lineNormal->Normal());
	}
	Circle CreateCircle(Point center, Point *outlinePoint, Point *planePoint, bool allThreePointsInsideCircle) {

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

		return Circle(center, radius, normal);
	}

	//rectangle
	Rectangle CreateRectangle(Point center, float X, float Y, float Roll/*[0,360]*/, Line normalLine) {
		Vector3 planeVector = Vector3(sin(Roll), cos(Roll), 0);
		Plane2DTo3D(&planeVector, 1, &normalLine.Normal(), Vector3());


		return Rectangle(X, Y, planeVector, center, normalLine.Normal());
	}

	Polygon CreatePolygon(std::vector <Point> pointsVector) { //minimum 3 points 

		return Polygon(pointsVector);
	}

	//if normal vector is not perpendicular to line, as normal is used normalized dot product between line and normal vector
	//if normal vector is same direction as line normal, exception occurred
	Rectangle AddWidthToLineVec(Line l, float width, Vector3 normalVector, short type) {
		/*type:
			0 - width/2 to left, width/2 to right
			1 - width to left
			2 - width to right
			*/
			//TODO
		float X = (float)l.distance;
		float Y = width;
		Point center;
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

		return Rectangle(X, Y, l.Normal(), center, normalVector);
	}
	//
	Rectangle AddWidthToLinePoint(Line l, float width, Point surfacePoint, short type) {
		/*type:
			0 - width/2 to left, width/2 to right
			1 - width to left
			2 - width to right
			*/
			//TODO
		Vector3 normalVector = crossProduct2Vectors(l.Normal(), surfacePoint - l.beginPoint).Normalize();
		return AddWidthToLineVec(l, width, normalVector, type);
	}


	//Circumscribed
	Line PerpendicularLineOnPoint(Point origin, Point p1, Point p2) {
		//move line points origin to center
		p1 = p1 - origin;
		p2 = p2 - origin;

		//rotate
		Vector3 temp = p1.Position;
		p1.Position.X = -temp.Y;
		p1.Position.Y = temp.X;

		temp = p2.Position;
		p2.Position.X = -temp.Y;
		p2.Position.Y = temp.X;

		//move points back
		p1 = p1 + origin;
		p2 = p2 + origin;
		return Line(p1, p2);
	}
	Circle CircumscribedTriangle(Triangle triangle) {
		//to 2D
		Vector3 normal;
		Vector3 arrayOfPoints[] = { triangle.p1.Position, triangle.p2.Position, triangle.p3.Position, Vector3() };
		Vector3 origin = triangle.p1.Position;
		Plane3DTo2D(arrayOfPoints, 3, &normal, origin);
		//Find center of circle
			//Find perpendicular line in middle of 2 random lines
				//	1.
		Point middle01 = LinearInterpolation_Percent(arrayOfPoints[0], arrayOfPoints[1], 0.5f);
		Line A = PerpendicularLineOnPoint(middle01, arrayOfPoints[0], arrayOfPoints[1]);
		//	2.
		Point middle12 = LinearInterpolation_Percent(arrayOfPoints[1], arrayOfPoints[2], 0.5f);
		Line B = PerpendicularLineOnPoint(middle12, arrayOfPoints[1], arrayOfPoints[2]);
		//find intersection of these lines
		arrayOfPoints[3]/*Point middle*/ = Intersection_Line_Line2D(A, B).Position;
		//find range of circle
			//distance between middle and any point
		float radius = (arrayOfPoints[3] - arrayOfPoints[0]).Distance();
		//to 3D
		Plane2DTo3D(arrayOfPoints, 4/* 3 triangle + 1 circle center*/, &normal, origin);
		//MovePlaneToBase();
		return Circle(arrayOfPoints[3], radius, normal);
	}





	Circle InscribedTriangle(Triangle *triangle) {
		//to2D
		Vector3 arrayOfPoints[4] = { triangle->p1.Position, triangle->p2.Position, triangle->p3.Position, Vector3()/*center*/ };
		Vector3 normal;
		Vector3 origin = triangle->p1.Position;
		Plane3DTo2D(arrayOfPoints, 3, &normal);

		//find Line between l12 and l13 (point p1)
			//find angle/2 - bisector
		Point v12 = LinearInterpolation_Distance(&triangle->p1, &triangle->p2, 1);
		Point v13 = LinearInterpolation_Distance(&triangle->p1, &triangle->p3, 1);

		//point in middle
		Point Middle1 = LinearInterpolation_Percent(v12, v13, 0.5f);
		Vector3 vectorFromPoint1 = (Middle1 - triangle->p1).Normalize();
		//find Line between l21 and l23 (point p1)
			//find angle/2 - bisector
		Point v21 = LinearInterpolation_Distance(&triangle->p2, &triangle->p1, 1);
		Point v23 = LinearInterpolation_Distance(&triangle->p2, &triangle->p3, 1);

		//
		Point Middle2 = LinearInterpolation_Percent(v21, v23, 0.5f);
		Vector3 vectorFromPoint2 = (Middle2 - triangle->p2).Normalize();

		//find middle between vectorFromPoint2 and vectorFromPoint2

		arrayOfPoints[3] = Intersection_Line_Line2D(Line(triangle->p1, vectorFromPoint1), Line(triangle->p2, vectorFromPoint2)).Position;
		//find range of lines (all distances between middle to lines are same)

		float radius = (float)MinLineBetweenLineAndPoint(Line(triangle->p1, triangle->p2), arrayOfPoints[3]).Distance();

		/*//find normal
		Vector3 arrayOfPoints[] = { triangle->p1.Position, triangle->p2.Position, triangle->p3.Position };
		Vector3 normal = crossProduct3Points(arrayOfPoints).Normalize();*/

		//to 3D
		Plane2DTo3D(arrayOfPoints, 4/* 3 triangle + 1 circle center*/, &normal, origin);
		return Circle(arrayOfPoints[3], radius, normal);

	}


}