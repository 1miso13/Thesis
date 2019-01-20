#pragma once
namespace operationType {
	enum OperationTypeEnum {
		///COMMAND LIST:

		///Point commands: //Commands returning points
		Point,//(string name, Point Parent = NULL, float visibility) //- Create point on position 0,0,0. Parent - If entered, position is relative, else absolute
		//Point(string name, float X, float Y, float Z, Point Parent = NULL, float visibility) //-Create point on position XYZ
		///	Example:
		//		Point("Name of point 1")	//Name can by written with "" or '' or without, Point is on absolute position [0,0,0]
		//		Point(NameOfPoint2)		//Name can by written with "" or '' or without
		//		Point('NameOfPoint3')	//Name can by written with "" or '' or without
		//		Point(NameOfPoint4,1.1,2.2,3.3)	//- Create visible Point on position [1,2,3] 
		//		Point(NameOfPoint4,1,2,3,true)	//- Create visible Point on position [1,2,3] 
		//		Point(NameOfPoint4,1,2,3,false)	//- Create invisible Point on position [1,2,3]
		//		Point(NameOfPoint4,1,2,3,NameOfParentPoint,true)	//- Create visible Point on relative position [1,2,3] from ParentPoint

		LinearInterpolationDist,
		LinearInterpolationPerc,//(string name, Point fromPoint, Point toPoint, float distance / percentage, float visibility)
		//	Example:
		//		LinearInterpolation(PointName, FromPoint, ToPoint, 50%)	//- Create Point in middle of entered points
		//		LinearInterpolation(PointName, FromPoint, ToPoint, 25%)	//- Create Point on position with distance 20% of first point and 80% of second point
		//		LinearInterpolation(PointName, FromPoint, ToPoint, 100)	//- Create Point on position with distance 100 from first point in angle to second point 

		Intersection_Plane_Line,//(string name, Line lineName, Sufrace surfaceName, float visibility)
		//	Alternative:
		//	Intersection(string name, Line lineName, Sufrace surfaceName)
		//	Example:
		//		Intersection_Plane_Line(PointName,  lineName, surfaceName) //- Create Point on position where Line with name "lineName" intersecting Surface with name "surfaceName"


		SurfaceCenterBoundingSquare,//(string name, Surface surfaceName, float visibility) //Create point on position of middle of entered surface
		//	Example:
		//		SurfaceCenterBoundingSquare(PointName, Circle)	//- Create Point on center of Circle
		//		SurfaceCenterBoundingSquare(PointName, Rectangle)	//- Create Point on middle of Rectangle
		//		SurfaceCenter(PointName, Polygon)		//- Create Point on middle of Polygon 
		//		SurfaceCenterBoundingSquare(PointName, Polygon)		//- Create Point on middle of Polygon - centroid (sum of points / count of points)

		SurfaceCenterAverage,//(string name, Surface surfaceName, float visibility) //Create point on avarage position of entered surface

		Centroid,//(string name, Triangle triangleName, float visibility)
		Incenter,//(string name, Triangle triangleName, float visibility)
		Circumcenter,//(string name, Triangle triangleName, float visibility)
		Orthocenter,//(string name, Triangle triangleName, float visibility)
		NinePointCenter,//(string name, Triangle triangleName, float visibility)

		ObjectCenterBoundingBox,//(string name, Object3D ObjectName, float visibility) //Create point on position of middle of entered object

		ObjectCenterAverage,//(string name, Object3D ObjectName, float visibility) //Create point on position of center of entered object

		LineFirstPoint,//(string name, Line lineName, float visibility)
		LineSecondPoint,//(string name, Line lineName, float visibility)




		///Line Commands:

		Line,//(string lineName, Point p1, Point p2, float visibility) //create line, where p1 is start point and p2 is end point

		LineNormalize,//(string lineName, Line l, float visibility)

		LineChangeLengthDist,//(string lineName, Line l, float distance, float visibility)
		LineChangeLengthPerc,//(string lineName, Line l, float percent, float visibility) //percent = (0;1>



		// these commands are based on page http://paulbourke.net/geometry/pointlineplane/
		MinLineBetweenLineAndLine,//(string lineName, Line l1, Line l2, float visibility)
		MinLineBetweenPointAndLine,//(string lineName, Point p, Line l, float visibility)
		MinLineBetweenPointAndSurface,//(string lineName, Point p, Surface s, float visibility)

		///Alternative:
		MinLine,//(string lineName, Object o1, Object o2, float visibility) //Supported are only : [Line,Line], [Point,Line], [Point, Surface]



		SurfaceNormal,//(string lineName, Surface s, float visibility) // return normal vector of surface



		LineRelocationByPoint,//(string lineName, Line l, Point p, float visibility)

		//OrthogonalLeastSquares,//(string lineName, Point p1, Point p2, Point p3, ..., float visibility) //min 3

		//CrossProductLP,//(string lineName, Line l, Point p, float visibility)
		CrossProduct,//(string lineName, Line l1, Line l2, float visibility)



	///Surface Commands:
	RectangleFromLine,
	//RectangleFromLine,//(string surfaceName, Line l, float width, Point surfacePoint, short type, float visibility)
	//RectangleFromLine(string surfaceName, Line l, float width, Vector3 normalVector, short type, float visibility)
//create Rectangle from Line l
/*type:
	0 - width/2 to left, width/2 to right
	1 - width to left
	2 - width to right
	*/
	//if normal vector is not perpendicular to line, as normal is used normalized dot product between line and normal vector
	//if normal vector is same direction as line normal, exception occure
	//If surface point is not on line l, exception occure
	Circle,//(string surfaceName, Point center, float radius, Line lineNormal, float visibility)
	//Circle(string surfaceName, Point center, Point outlinePoint, Point planePoint, float visibility)

	Triangle,//(string surfaceName, Line l, Point p, float visibility)
	//Triangle(string surfaceName, Point p1, Point p2, Point p3, float visibility)

	//rectangle
	Rectangle,//(string surfaceName, Point center, float X, float Y, float Roll/*[0,360]*/, Line normal, float visibility)

	Polygon,//(string surfaceName, Point p1, Point p2, Point p3, ..., float visibility)//minimum 3 points 


	Circumscribed,//(string surfaceName, Triangle t, float visibility) //Create circle over triangle
	Inscribed,//(string surfaceName, Triangle t, float visibility)		//Create circle in triangle

///Objects Commands:

Pyramid,//(string objectName, Surface s, float distance, float visibility) //Create Pyramid by distance from center
//Pyramid(string objectName, Surface s, Point p, float visibility) //Create Pyramid by Point

Extrude,//(string objectName, Surface s, float distance, float visibility) //add width to plane

//SpericalCurvedSurface,//(string objectName, Surface s, float distance, float visibility)


//Cylinder,//(string objectName, Line l, float radius, float visibility)

INVALID
	};
	

}