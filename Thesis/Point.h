#pragma once
#ifndef POINT_CLASS
#define POINT_CLASS
#include "GeometricObject.h"
#include "Vector.h"
#include <list>
namespace Object {
	class Point :
		public GeometricObject
	{
	public:
		//Parameters
		Vector3 Position;

		//functions
		Point();
		Point(float X, float Y, float Z);
		Point(Vector3 pos);
		~Point() {

		}

		Vector3 GetPosition();




		inline void operator -=(Point& A) {
			this->Position = this->Position - A.Position;
		}


		Point operator =(Vector3 vec) {
			Point a(vec.X, vec.Y, vec.Z);
			return a;
		}
		Point operator =(Vector2 vec) {
			return Point(vec.X, vec.Y, 0);
		}
	private:
		void createMesh() {
			vertices.push_back(Position.X);
			vertices.push_back(Position.Y);
			vertices.push_back(Position.Z);
			indices.push_back(0);
			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(0);
		}
	};
	inline Vector3 operator -(Point A, Point B) {
		return Vector3(A.Position - B.Position);
	}
	inline Point operator +(Point A, Point B) {
		float X = A.Position.X + B.Position.X;
		float Y = A.Position.Y + B.Position.Y;
		float Z = A.Position.Z + B.Position.Z;
		return Point(X, Y, Z);
	}
	inline Point operator /(Point A, float B) {
		float X = A.Position.X / B;
		float Y = A.Position.Y / B;
		float Z = A.Position.Z / B;
		return Point(X, Y, Z);
	}
	inline Point operator *(Point A, float B) {
		float X = A.Position.X * B;
		float Y = A.Position.Y * B;
		float Z = A.Position.Z * B;
		return Point(X, Y, Z);
	}
	inline Point operator *(float B, Point A) {
		float X = A.Position.X * B;
		float Y = A.Position.Y * B;
		float Z = A.Position.Z * B;
		return Point(X, Y, Z);
	}
}

#endif