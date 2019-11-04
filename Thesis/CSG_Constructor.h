#pragma once
#include "GeometricObject.h"

namespace csg {
	void CSG_union(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB);
	void CSG_intersection(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB);
	void CSG_minus(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB);
	void CSG_XOR(Object::GeometricObject * objectOUT, Object::GeometricObject * objectA, Object::GeometricObject * objectB);
}
