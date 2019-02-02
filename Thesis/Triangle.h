#pragma once
#include "Surface.h"
#include "Geometry.h"
namespace Object {
	class Triangle :
		public Surface
	{
	public:
		Point p1;
		Point p2;
		Point p3;

		Triangle(Point p1, Point p2, Point p3)
		{
			this->p1 = p1;
			this->p2 = p2;
			this->p3 = p3;

			Vector3 AB = p2 - p1;
			Vector3 AC = p3 - p1;
			normal = crossProduct2Vectors(AB, AC).Normalize();
			center = ((p1 + p2 + p3) / 3);
			GeometricType = TRIANGLE;
		}


		~Triangle()
		{
		}

		void CalculatePerimeter()
		{
			float a = (p2 - p1).Distance();
			float b = (p3 - p2).Distance();
			float c = (p1 - p3).Distance();

			perimeter = (double)a + (double)b + (double)c;
		}

		void CalculateArea()
		{
			Vector3 AB = p2 - p1;
			Vector3 AC = p3 - p1;
			area = crossProduct2Vectors(AB, AC).Distance() / 2;
		}
	};

}