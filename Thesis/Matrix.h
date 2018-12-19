#pragma once
#include "vector.h"
class Matrix
{
public:
	double m00=0, m01=0, m02=0;
	double m10=0, m11=0, m12=0;
	double m20=0, m21=0, m22=0;
	Matrix();
	~Matrix();
};



inline Matrix::Matrix()
{
}


inline Matrix::~Matrix()
{
}

inline Vector3 operator * ( Matrix m, Vector3 vec) {
	Vector3 ret = Vector3();
	ret.X = (float)(m.m00 * vec.X + m.m01 * vec.Y + m.m02 * vec.Z);
	ret.Y = (float)(m.m10 * vec.X + m.m11 * vec.Y + m.m12 * vec.Z);
	ret.Z = (float)(m.m20 * vec.X + m.m21 * vec.Y + m.m22 * vec.Z);
	return ret;
}