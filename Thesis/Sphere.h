#pragma once
#include "Shape3D.h"
#include "Point.h"
namespace Object {
	class Sphere :
		public Shape3D
	{
	public:
		Point center;
		float radius;
		Sphere(Point center, float radius);
		~Sphere();
		void CalculateVolume();
		void CalculateSurfaceArea();
	};


	inline Sphere::Sphere(Point center, float radius)
	{
		this->center = center;
		this->radius = radius;
		GeometricType = SPHERE_ObjectType;
	}


	inline Sphere::~Sphere()
	{
	}

	inline void Sphere::CalculateVolume()
	{

		volume = (4. * atan(1.) * radius * radius * radius * 4) / 3;
	}

	inline void Sphere::CalculateSurfaceArea()
	{
		surfaceArea = 4 * 4. * atan(1.) * radius * radius;
	}
}