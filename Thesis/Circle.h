#pragma once
#include "Surface.h"
namespace Object {
	class Circle :
		public Surface
	{
	public:
		float radius;
		Circle(Point center, float radius, Vector3 normal);
		void CalculatePerimeter();

		void CalculateArea();

		void CreateMesh();
	};

}