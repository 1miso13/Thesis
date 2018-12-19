#pragma once
struct Vector3
{
	float X, Y, Z;
	Vector3(float X, float Y, float Z) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	Vector3() {
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
	}

	Vector3 Normalize() {
		//distance
		float dist = sqrt(X * X + Y * Y + Z * Z);
		return Vector3( X / dist,  Y / dist,  Z / dist);
	}
	float Distance()
	{	
		return sqrt(X*X + Y*Y + Z*Z);
	}
	Vector3& operator +=(Vector3& B) {
		this->X = this->X + B.X;
		this->X = this->Y + B.Y;
		this->X = this->Z + B.Z;
		return *this;
	}
	bool operator ==(Vector3& B) {
		if (this->X == B.X && this->Y == B.Y && this->Z == B.Z)
		{
			return true;
		}
		return false;
	}
	bool operator !=(Vector3& B) {
		return !(*this == B);
	}
	static float Dot(Vector3 A, Vector3 B);
};
struct Vector2
{
	float X, Y;
	Vector2(float X, float Y) {
		this->X = X;
		this->Y = Y;
	}
};


inline Vector3 operator -(Vector3 A, Vector3 B) {
	float X = A.X - B.X;
	float Y = A.Y - B.Y;
	float Z = A.Z - B.Z;
	return Vector3(X, Y, Z);
}
inline Vector3 operator +(Vector3 A, Vector3 B) {
	float X = A.X + B.X;
	float Y = A.Y + B.Y;
	float Z = A.Z + B.Z;
	return Vector3(X, Y, Z);
}
inline Vector3 operator *(float A, Vector3 B) {
	float X = A * B.X;
	float Y = A * B.Y;
	float Z = A * B.Z;
	return Vector3(X, Y, Z);
}
inline Vector3 operator *(double A, Vector3 B) {
	float X = (float)(A * B.X);
	float Y = (float)(A * B.Y);
	float Z = (float)(A * B.Z);
	return Vector3(X, Y, Z);
}
inline Vector3 operator *(Vector3 B, double A) {
	float X = (float)(A * B.X);
	float Y = (float)(A * B.Y);
	float Z = (float)(A * B.Z);
	return Vector3(X, Y, Z);
}
inline Vector3 operator *(Vector3 B, float A) {
	float X = A * B.X;
	float Y = A * B.Y;
	float Z = A * B.Z;
	return Vector3(X, Y, Z);
}

inline Vector3 operator /(Vector3 A, int B) {
	float X = A.X / B;
	float Y = A.Y / B;
	float Z = A.Z / B;
	return Vector3(X, Y, Z);
}