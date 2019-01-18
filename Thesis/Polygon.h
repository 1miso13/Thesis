#pragma once
#include "pch.h"
#include <vector>
class Polygon :
	public Surface
{
public:
	std::vector <Point> points;
	Polygon(std::vector <Point> points);
	~Polygon();
	void CalculatePerimeter();
	void CalculateArea();
};

