#pragma once
#include <vector>
class CalculateMeshNormals
{
public:
	static void calculateNormals(std::vector<int> indices, std::vector <float> vertex, std::vector <float> *verticesNormal);
	CalculateMeshNormals(){}
	~CalculateMeshNormals(){}
};

