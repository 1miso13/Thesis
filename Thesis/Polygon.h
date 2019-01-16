#pragma once
#include "pch.h"
#include <vector>
class Polygon :
	public Surface
{
public:
	std::vector <Point> pointsVector;
	Polygon(std::vector <Point> pointsVector);
	~Polygon();
};

