#pragma once
#include "pch.h"
class Triangle :
	public Surface
{
public:
	Point p1;
	Point p2;
	Point p3;
	Triangle();
	~Triangle();
};

