#pragma once
#include "pch.h"
#include <vector>
class Shape :
	public Surface
{
public:
	std::vector <Point> pointsVector;
	Shape(std::vector <Point> pointsVector);
	~Shape();
};

