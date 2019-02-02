#pragma once
#include "Surface.h"
namespace Object {
	class Circle :
		public Surface
	{
	public:
		float radius;
		Circle(Point center, float radius, Vector3 normal) {
			this->center = center;
			this->radius = radius;
			this->normal = normal;
			GeometricType = CIRCLE;
		}
		void CalculatePerimeter()
		{
			perimeter = 2 * (4. * atan(1.))/*PI*/ * radius;
		}

		void CalculateArea()
		{
			area = (4. * atan(1.)) * radius * radius;
		}


		~Circle()
		{
		}

	};

}