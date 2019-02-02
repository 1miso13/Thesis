#pragma once
#ifndef LINE_CLASS
#define LINE_CLASS
#include "GeometricObject.h"
#include "Point.h"
namespace Object {
	class Line :
		public GeometricObject
	{
	private:
		void DistanceCalc();
	public:
		Point beginPoint;
		Point endPoint;
		double distance;

		Line(Point beginPoint, Point endPoint);
		Line(Vector3 beginPoint, Vector3 endPoint);
		Line(Vector2 beginPoint, Vector2 endPoint);
		Line(Vector3 point);
		Line();
		~Line();
		Vector3 Normal();
		float Distance();
		Vector3 Middle();
		Vector3 Vector();
	};

	inline Line::Line(Point beginPoint, Point endPoint)
	{
		this->beginPoint = beginPoint;
		this->endPoint = endPoint;
		DistanceCalc();
		GeometricType = LINE;
	}

	inline Line::Line(Vector3 beginPoint, Vector3 endPoint)
	{
		this->beginPoint = beginPoint;
		this->endPoint = endPoint;
		DistanceCalc();
		GeometricType = LINE;
	}

	inline Line::Line(Vector2 beginPoint, Vector2 endPoint)
	{
		DistanceCalc();
		GeometricType = LINE;
	}

	inline Line::Line(Vector3 point)
	{
		this->beginPoint = Vector3(0, 0, 0);
		this->endPoint = point;
		DistanceCalc();
		GeometricType = LINE;
	}
	inline Line::Line()
	{
		this->beginPoint = Vector3(0, 0, 0);
		this->endPoint = Vector3(0, 0, 0);
		DistanceCalc();
		GeometricType = LINE;
	}


	inline Line::~Line()
	{
	}

	inline Vector3 Line::Vector()
	{
		return this->endPoint - this->beginPoint;
	}


	inline Vector3 Line::Normal()
	{
		return  Vector().Normalize();

	}
	inline float  Line::Distance()
	{
		Vector3 tmp = this->endPoint - this->beginPoint;
		return tmp.Distance();

		//return	sqrt(tmp.X*tmp.X + tmp.Y*tmp.Y + tmp.Z*tmp.Z);
	}

	inline void Line::DistanceCalc()
	{
		Vector3 tmp = this->endPoint - this->beginPoint;
		distance = tmp.Distance();

		//return	sqrt(tmp.X*tmp.X + tmp.Y*tmp.Y + tmp.Z*tmp.Z);
	}

	inline Vector3 Line::Middle()
	{

		return ((this->endPoint + this->beginPoint) / 2.0f).Position;
	}
}
#endif
