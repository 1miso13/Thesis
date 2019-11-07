#pragma once
#include <vector>
#include <glm/glm.hpp>
class EarClippingTriangulator {
	std::vector<glm::vec3> *verticies = NULL;
	std::vector <int> *indicies = NULL;
	std::vector <unsigned int> index;
	unsigned int actualIndex;
	unsigned int nextIndex;
	unsigned int prevIndex;

public:
	void Init(std::vector<glm::vec3>  *verticies, std::vector <int>  *indicies);
	bool Step();
	void NextTriangle();
	void Triangulate();
    void Reset();
private:
	bool ClockwiseTest();
	bool isInside(glm::vec3 & p, glm::vec3 & t1, glm::vec3 & t2, glm::vec3 & t3);
};
