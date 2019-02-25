#include "pch.h"
#include "Circle.h"


namespace Object {
	Circle::Circle(Point center, float radius, Vector3 normal) {
		this->center = center;
		this->radius = radius;
		this->normal = normal;
		GeometricType = CIRCLE_ObjectType;
	}
	void Circle::CalculatePerimeter()
	{
		perimeter = 2 * (4. * atan(1.))/*PI*/ * radius;
	}

	void Circle::CalculateArea()
	{
		area = (4. * atan(1.)) * radius * radius;
	}


}