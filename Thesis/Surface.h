#pragma once
#include "GeometricObject.h"
#include "Point.h"
namespace Object {
	class Surface :
		public GeometricObject
	{
	protected:
		double perimeter=0;
		double area=0;
	private:
		bool perimeterSet = false;
		bool areaSet = false;
	public:
		Vector3 normal;
		Point center;
		virtual double GetPerimeter() final {
			if (perimeterSet)
			{
				perimeterSet = true;
				CalculatePerimeter();
			}
			return perimeter;
		}
		virtual double GetArea() final {
			if (areaSet)
			{
				areaSet = true;
				CalculateArea();
			}
			return area;
		}
		Surface();
		~Surface() {

		}

		/// <summary>
		/// Create polygonal mesh
		/// Must be overloaded
		/// </summary>
		virtual void CreateMesh() = 0;
	private:
		virtual void CalculatePerimeter() = 0;
		virtual void CalculateArea() = 0;
	};

}