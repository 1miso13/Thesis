#pragma once
#include "Shape3D.h"
#include "Point.h"
#ifndef CIRCLE_SHAPE_COUNT
	#define CIRCLE_SHAPE_COUNT 15
#endif // !CIRCLE_SHAPE_COUNT

namespace Object {
	class Sphere :
		public Shape3D
	{
	public:
		Point center;
		float radius;
		Sphere(Point center, float radius);
		void CalculateVolume();
		void CalculateSurfaceArea();
	private:
		void CreateMesh();
	};


	inline Sphere::Sphere(Point center, float radius)
	{
		this->center = center;
		this->radius = radius;
		GeometricType = SPHERE_ObjectType;
		CreateMesh();
	}

	inline void Sphere::CalculateVolume()
	{

		volume = (4. * atan(1.) * radius * radius * radius * 4) / 3;
	}

	inline void Sphere::CalculateSurfaceArea()
	{
		surfaceArea = 4 * 4. * atan(1.) * radius * radius;
	}
	inline void Sphere::CreateMesh() {
		int N = CIRCLE_SHAPE_COUNT;
		int M = CIRCLE_SHAPE_COUNT;
		float MathPI = 3.14159265f;

		//at begin and and create only one point, and connect it to all vertices at first row
		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
		int j = CIRCLE_SHAPE_COUNT-1;
		for (int n = 0; n < N; n++)
		{
			normals.push_back(sin(MathPI / M) * cos(2 * MathPI * n / N) );//X
			normals.push_back(cos(MathPI / M));//Y
			normals.push_back(sin(MathPI / M) * sin(2 * MathPI * n / N));//Z

			indices.push_back(0);
			indices.push_back(n+1);
			indices.push_back(j + 1);
			j = n;
		}
		1;//row begin index
		for (int m = 1; m < M-1; m++)
		{
			int j= CIRCLE_SHAPE_COUNT - 1;
			for (int n = 0; n < N; n++)
			{
				normals.push_back(sin(MathPI * m / M) * cos(2 * MathPI * n / N));//X
				normals.push_back(cos(MathPI * m / M));//Y
				normals.push_back(sin(MathPI * m / M) * sin(2 * MathPI * n / N));//Z


				indices.push_back(((m - 1) * N + 1) + j);	//		1*		<-	row before	- index before
				indices.push_back((m	*	 N + 1) + n);	//		 * *
				indices.push_back((m	*	 N + 1) + j);	//		2* * *3	<-	actual row	- index before, actual index


				indices.push_back(((m - 1) * N + 1) + j);	//		1* * *3	<-	row before	- index before,  actual index
				indices.push_back(((m - 1) * N + 1) + n);	//		   * *
				indices.push_back((m	*	 N + 1) + n);	//		     *2	<-	actual row	-  actual index

				j = n;
			}
			//m*N + 1;//row begin index
		}

		normals.push_back(0);
		normals.push_back(-1);
		normals.push_back(0);

		j = CIRCLE_SHAPE_COUNT - 1;
		for (int n = 0; n < N; n++)
		{
			indices.push_back((M - 1 - 1)*N + j + 1);	//		1* * *3	<-	row before	- index before,  actual index
			indices.push_back((M - 1 - 1)*N + n + 1);	//		  * *
			indices.push_back((M - 1) *   N	    + 1);	//		   *2	<-	actual row	-  actual index
			j = n;
		}

		//generate normals
		//calculateNormals();
		for (size_t i = 0; i < normals.size(); i+=3)
		{
			vertices.push_back(normals[i] * radius + center.Position.X);
			vertices.push_back(normals[i+1] * radius + center.Position.Y);
			vertices.push_back(normals[i+2] * radius + center.Position.Z);
		}
	}
}