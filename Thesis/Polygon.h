#pragma once
#include "Surface.h"
#include "Point.h"
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

