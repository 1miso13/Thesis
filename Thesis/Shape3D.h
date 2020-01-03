#pragma once
#include "GeometricObject.h"
#include "Geometry.h"

namespace Object {
	class Shape3D :
		public GeometricObject
	{
	private:
		/// <summary>
		/// After creating object call this 
		/// </summary>
		void virtual CalculateVolume();
		/// <summary>
		/// After creating object call this
		/// </summary>
		void virtual CalculateSurfaceArea();
	protected:
		double volume=0;
		double surfaceArea=0;
	private:
		bool volumeSet = false;
		bool surfaceAreaSet = false;
	public:
		virtual double GetVolume() final {
			if (volumeSet)
			{
				volumeSet = true;
				CalculateVolume();
			}
			return volume;
		}
		virtual double GetSurfaceArea() final {
			if (surfaceAreaSet)
			{
				surfaceAreaSet = true;
				CalculateSurfaceArea();
			}
			return surfaceArea;
		}
		Shape3D();
	protected:
		void virtual CreateMesh() {

		}

	};




}