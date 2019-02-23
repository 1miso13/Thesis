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

		Triangle(Point p1, Point p2, Point p3);


		~Triangle();

		void CalculatePerimeter();

		void CalculateArea();
	};

}