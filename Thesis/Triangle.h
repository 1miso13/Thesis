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

		void setP1(Point p);
		void setP1(float x, float y, float z);
		void setP2(Point p);
		void setP2(float x, float y, float z);
		void setP3(Point p);
		void setP3(float x, float y, float z);


		Triangle(Point p1, Point p2, Point p3);


		~Triangle();

		void Initialize();

		void CalculatePerimeter();

		void CalculateArea();
		void CreateMesh();
	};

}