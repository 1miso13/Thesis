#pragma once
#include "Surface.h"
#include "Point.h"
#include <vector>
#include "Geometry.h"
namespace Object {
	class Polygon :
		public Surface
	{
	public:
		std::vector <Point> points;
		Polygon(std::vector <Point> points);

		~Polygon();
		void CalculatePerimeter();
		void CalculateArea();
		void CreateMesh();
	};

}