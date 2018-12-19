#pragma once
namespace operationType {
	enum OperationTypeEnum {
		///COMMAND LIST:

		///Point commands: //Commands returning points
		Point,//(string name, Point Parent = NULL, bool visible = true) //- Create point on position 0,0,0. Parent - If entered, position is relative, else absolute
		//Point(string name, float X, float Y, float Z, Point Parent = NULL, bool visible = true) //-Create point on position XYZ
		///	Example:
		//		Point("Name of point 1")	//Name can by written with "" or '' or without, Point is on absolute position [0,0,0]
		//		Point(NameOfPoint2)		//Name can by written with "" or '' or without
		//		Point('NameOfPoint3')	//Name can by written with "" or '' or without
		//		Point(NameOfPoint4,1.1,2.2,3.3)	//- Create visible Point on position [1,2,3] 
		//		Point(NameOfPoint4,1,2,3,true)	//- Create visible Point on position [1,2,3] 
		//		Point(NameOfPoint4,1,2,3,false)	//- Create invisible Point on position [1,2,3]
		//		Point(NameOfPoint4,1,2,3,NameOfParentPoint,true)	//- Create visible Point on relative position [1,2,3] from ParentPoint

		LinearInterpolationDist,
		LinearInterpolationPerc,//(string name, Point fromPoint, Point toPoint, float distance / percentage, bool visible = true)
		//	Example:
		//		LinearInterpolation(PointName, FromPoint, ToPoint, 50%)	//- Create Point in middle of entered points
		//		LinearInterpolation(PointName, FromPoint, ToPoint, 25%)	//- Create Point on position with distance 20% of first point and 80% of second point
		//		LinearInterpolation(PointName, FromPoint, ToPoint, 100)	//- Create Point on position with distance 100 from first point in angle to second point 

		Intersection_Plane_Line,//(string name, Line lineName, Sufrace surfaceName, bool visible = true)
		//	Alternative:
		//	Intersection(string name, Line lineName, Sufrace surfaceName)
		//	Example:
		//		Intersection_Plane_Line(PointName,  lineName, surfaceName) //- Create Point on position where Line with name "lineName" intersecting Surface with name "surfaceName"

		SurfaceMiddle,//(string name, Surface surfaceName, bool visible = true) //Create point on position of middle of entered surface
		//	Example:
		//		SurfaceMiddle(PointName, Circle)	//- Create Point on center of Circle
		//		SurfaceMiddle(PointName, Rectangle)	//- Create Point on middle of Rectangle
		//		SurfaceCenter(PointName, Shape)		//- Create Point on middle of shape 
		//		SurfaceMiddle(PointName, Shape)		//- Create Point on middle of shape - centroid (sum of points / count of points)

		ObjectMiddle,//(string name, Object3D ObjectName, bool visible = true) //Create point on position of middle of entered object
		ObjectCenter,//(string name, Object3D ObjectName, bool visible = true) //Create point on position of center of entered object

		LineFirstPoint,//(string name, Line lineName, bool visible = true)
		LineSecondPoint,//(string name, Line lineName, bool visible = true)




		///Line Commands:

		Line,//(string lineName, Point p1, Point p2, bool visible = true) //create line, where p1 is start point and p2 is end point

		LineNormalize,//(string lineName, Line l, bool visible = true)

		LineChangeLengthDist,//(string lineName, Line l, float distance, bool visible = true)
		LineChangeLengthPerc,//(string lineName, Line l, float percent, bool visible = true) //percent = (0;1>



		// these commands are based on page http://paulbourke.net/geometry/pointlineplane/
		MinLineBetweenLineAndLine,//(string lineName, Line l1, Line l2, bool visible = true)
		MinLineBetweenPointAndLine,//(string lineName, Point p, Line l, bool visible = true)
		MinLineBetweenPointAndSurface,//(string lineName, Point p, Surface s, bool visible = true)

		///Alternative:
		MinLine,//(string lineName, Object o1, Object o2, bool visible = true) //Supported are only : [Line,Line], [Point,Line], [Point, Surface]



		SurfaceNormal,//(string lineName, Surface s, bool visible = true) // return normal vector of surface



		LineRelocationByPoint,//(string lineName, Line l, Point p, bool visible = true)

		//OrthogonalLeastSquares,//(string lineName, Point p1, Point p2, Point p3, ..., bool visible = true) //min 3

		//CrossProductLP,//(string lineName, Line l, Point p, bool visible = true)
		CrossProduct,//(string lineName, Line l1, Line l2, bool visible = true)



	///Surface Commands:

	AddWidthToLine,//(string surfaceName, Line l, float width, Point surfacePoint, short type, bool visible = true)
	//AddWidthToLine(string surfaceName, Line l, float width, Vector3 normalVector, short type, bool visible = true)
//create Rectangle from Line l
/*type:
	0 - width/2 to left, width/2 to right
	1 - width to left
	2 - width to right
	*/
	//if normal vector is not perpendicular to line, as normal is used normalized dot product between line and normal vector
	//if normal vector is same direction as line normal, exception occure
	//If surface point is not on line l, exception occure
	Circle,//(string surfaceName, Point center, float radius, Line lineNormal, bool visible = true)
	//Circle(string surfaceName, Point center, Point outlinePoint, Point planePoint, bool visible = true)

	Triangle,//(string surfaceName, Line l, Point p, bool visible = true)
	//Triangle(string surfaceName, Point p1, Point p2, Point p3, bool visible = true)

	//rectangle
	Rectangle,//(string surfaceName, Point center, float X, float Y, float Roll/*[0,360]*/, Line normal, bool visible = true)

	Shape,//(string surfaceName, Point p1, Point p2, Point p3, ..., bool visible = true)//minimum 3 points 


	Circumscribed,//(string surfaceName, Triangle t, bool visible = true) //Create circle over triangle
	Inscribed,//(string surfaceName, Triangle t, bool visible = true)		//Create circle in triangle

///Objects Commands:

Pyramid,//(string objectName, Surface s, float distance, bool visible = true) //Create Pyramid by distance from center
//Pyramid(string objectName, Surface s, Point p, bool visible = true) //Create Pyramid by Point

To3D,//(string objectName, Surface s, float distance, bool visible = true) //add width to 

SpericalCurvedSurface,//(string objectName, Surface s, float distance, bool visible = true)


Cylinder,//(string objectName, Line l, float radius, bool visible = true)

INVALID
	};
	

}