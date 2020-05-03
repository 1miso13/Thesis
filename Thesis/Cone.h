#pragma once
#include "Point.h"
#include "Shape3D.h"
#include "Surface.h"
#include "Line.h"
#include "Triangle.h"
#include "Circle.h"
#include "Geometry.h"
#include "Rectangle.h"
#include "Polygon.h"
namespace Object {
	class Cone :
		public Object::Shape3D
	{
	public:
		/// <summary>
		/// 1-circle
		/// 2-triangle
		/// 3-rectangle
		/// 4-polygon
		/// </summary>
		short BaseType;

		Point apex;
		Surface *base;
		float height=0;
		Cone(Point apex, Surface* base);
		Cone(float height, Surface* base);
		~Cone();

		void CalculateHeight();

		/// <summary>
		/// only with height
		/// </summary>
		void CalculateVolume();
		/// <summary>
		/// only with height
		/// </summary>
		void CalculateSurfaceArea();

		short GetBaseType();
	private:
		void CreateMesh();
	};

}