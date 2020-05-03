#include "pch.h"
#include "Line.h"
#include "Point.h"
namespace Object {
	
	 Line::Line(Point beginPoint, Point endPoint)
	{
		this->beginPoint = beginPoint;
		this->endPoint = endPoint;
		DistanceCalc();
		GeometricType = LINE_ObjectType;
		CreateMesh();
	}

	 Line::Line(Vector3 beginPoint, Vector3 endPoint)
	{
		this->beginPoint.Position = beginPoint;
		this->endPoint.Position = endPoint;
		DistanceCalc();
		GeometricType = LINE_ObjectType;
		CreateMesh();
	}

	 Line::Line(Vector2 beginPoint, Vector2 endPoint)
	{
		DistanceCalc();
		GeometricType = LINE_ObjectType;
		CreateMesh();
	}

	 Line::Line(Vector3 point)
	{
		this->beginPoint = Vector3(0, 0, 0);
		this->endPoint.Position = point;
		DistanceCalc();
		GeometricType = LINE_ObjectType;
		CreateMesh();
	}
	 Line::Line()
	{
		this->beginPoint = Vector3(0, 0, 0);
		this->endPoint = Vector3(0, 0, 0);
		DistanceCalc();
		GeometricType = LINE_ObjectType;
		CreateMesh();
	}


	 Line::~Line()
	{
	}

	 Vector3 Line::Vector()
	{
		return this->endPoint - this->beginPoint;
	}


	 Vector3 Line::Normal()
	{
		return  Vector().Normalize();

	}
	 float  Line::Distance()
	{
		Vector3 tmp = this->endPoint - this->beginPoint;
		return tmp.Distance();

		//return	sqrt(tmp.X*tmp.X + tmp.Y*tmp.Y + tmp.Z*tmp.Z);
	}

	 void Line::DistanceCalc()
	{
		Vector3 tmp = this->endPoint - this->beginPoint;
		distance = tmp.Distance();

		//return	sqrt(tmp.X*tmp.X + tmp.Y*tmp.Y + tmp.Z*tmp.Z);
	}

	 Vector3 Line::Middle()
	{

		return ((this->endPoint + this->beginPoint) / 2.0f).Position;
	}
	 void Line::CreateMesh() {
		 vertices.push_back(beginPoint.Position.X);
		 vertices.push_back(beginPoint.Position.Y);
		 vertices.push_back(beginPoint.Position.Z);
		 vertices.push_back(endPoint.Position.X);
		 vertices.push_back(endPoint.Position.Y);
		 vertices.push_back(endPoint.Position.Z);
		 indices.push_back(0);
		 indices.push_back(1);
		 normals.push_back(0);
		 normals.push_back(0);
		 normals.push_back(0);

		 normals.push_back(0);
		 normals.push_back(0);
		 normals.push_back(0);
	 }
}