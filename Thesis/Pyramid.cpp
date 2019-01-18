
#include "GeometricOperation.h"
#include "pch.h"
#include "Pyramid.h"

#define M_PI           3.14159265358979323846
#define INTEGRAL_STEP_COUNT 100

/// <summary>
/// 
/// </summary>
/// <param name="apex"></param>
/// <param name="base"></param>
/// <param name="BaseType">1-circle
/// 2-triangle
/// 3-rectangle
/// 4-polygon</param>
Pyramid::Pyramid(Point apex, Surface * base, short BaseType)
{
	this->apex = apex;
	this->base = base;
	this->BaseType = BaseType;
	CalculateHeight();
}
/// <summary>
/// 
/// </summary>
/// <param name="height"></param>
/// <param name="base"></param>
/// <param name="BaseType">1-circle
/// 2-triangle
/// 3-rectangle
/// 4-polygon</param>
Pyramid::Pyramid(float height, Surface * base, short BaseType)
{
	this->height = height;
	this->apex = Point(base->center) + base->normal*height;
	this->base = base;
	this->BaseType = BaseType;
}

Pyramid::~Pyramid()
{
}

/// <summary>
/// If not entered 
/// </summary>
void Pyramid::CalculateHeight()
{
	double distPointToPlane = DotProduct((this->apex.Position - this->base->center), this->base->normal);
	Point p2 = this->apex.Position - (this->base->normal * distPointToPlane);
	height = Line(p2, this->apex).Distance();
}

void Pyramid::CalculateVolume()
{
	volume = base->area * height * 1 / 3;
}

void Pyramid::CalculateSurfaceArea()
{
	surfaceArea = base->area;

	//rozdielne pre rozdielne tvary
	if (BaseType == 1) {// circle

		//Tato metoda je nepresna!
		//kruhovu zakladnu rozdelime na N casti
		//každú èas spojíme s vrcholom
		//vznikne N trojuholniko
		//vypocitame a scitame plochu trojuholnikov
		Vector3 perpendicularVector = Vector3(base->normal.Y, -base->normal.X, 0) * ((Circle*)base)->radius;

		double stepAlpha = M_PI / INTEGRAL_STEP_COUNT;
		double alpha = 0;
		for (size_t i = 0; i < INTEGRAL_STEP_COUNT; i++)
		{
			Vector3 AB = (this->base->center + (cos(alpha)*perpendicularVector + (sin(alpha))*crossProduct2Vectors(base->normal, perpendicularVector))) - this->apex;
			Vector3 AC = (this->base->center + (cos(alpha + stepAlpha)*perpendicularVector + (sin(alpha + stepAlpha))*crossProduct2Vectors(base->normal, perpendicularVector))) - this->apex;
			surfaceArea += crossProduct2Vectors(AB, AC).Distance() / 2;
			alpha += stepAlpha;
		}

	}
	else
		if (BaseType == 2)//triangle
		{

			Vector3 AA = ((Triangle*)base)->p1 - this->apex;
			Vector3 BA = ((Triangle*)base)->p1 - this->apex;
			Vector3 CA = ((Triangle*)base)->p3 - this->apex;
			surfaceArea += crossProduct2Vectors(AA, BA).Distance() / 2;
			surfaceArea += crossProduct2Vectors(BA, CA).Distance() / 2;
			surfaceArea += crossProduct2Vectors(CA, AA).Distance() / 2;
		}
		else
			if (BaseType == 3)//rectangle
			{
			//TODO rectangle base pyramid - surface area

			}
			else
				if (BaseType == 4)//polygon
				{

					Polygon* basePolygon = (Polygon*)base;
					for (size_t i = 1; i < basePolygon->points.size(); i++)
					{
						Vector3 AA = basePolygon->points[i - 1] - this->apex;
						Vector3 BA = basePolygon->points[i] - this->apex;
						surfaceArea += crossProduct2Vectors(AA, BA).Distance() / 2;
					}

					Vector3 AA = basePolygon->points[basePolygon->points.size() - 1] - this->apex;
					Vector3 BA = basePolygon->points[0] - this->apex;
					surfaceArea += crossProduct2Vectors(AA, BA).Distance() / 2;
				}
}
