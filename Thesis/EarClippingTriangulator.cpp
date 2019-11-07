#include "pch.h"
#include "EarClippingTriangulator.h"

bool EarClippingTriangulator::ClockwiseTest() {
	float sum = 0;

	int j = ((int)this->verticies->size()) - 1;
	for (int i = 0; i < this->verticies->size(); i++)
	{
		sum += (verticies->at(i).x - verticies->at(j).x)* (verticies->at(i).y + verticies->at(j).y);
		j = i;
	}


	return sum > 0;
}

bool EarClippingTriangulator::isInside(glm::vec3 & p, glm::vec3 & t1, glm::vec3 & t2, glm::vec3 & t3)
{
	bool a = glm::cross(t1- t2, p- t2).z > 0;
	bool b = glm::cross(t2- t3, p- t3).z > 0;
	bool c = glm::cross(t3- t1, p- t1).z > 0;
	return a && b && c;
}

void EarClippingTriangulator::Init(std::vector<glm::vec3>  *verticies, std::vector <int>  *indicies)
{
	this->verticies = verticies;
	this->indicies = indicies;
	Reset();
}

/// <summary>
/// Make one step
/// If there are no collisions - create triangle
/// otherwise - move to next points
/// </summary>
/// <returns>Return true, if new triangle is created</returns>
bool EarClippingTriangulator::Step()
{
	bool inside = false;
	//test, if no point is in the triangle 
	for (size_t i = 0; i < verticies->size(); i++)
	{
		if (isInside(verticies->at(i), verticies->at(index[prevIndex]), verticies->at(index[actualIndex]), verticies->at(index[nextIndex])))
		{
			inside = true;
			break;
		}
	}

	float convex = (float)glm::cross(verticies->at(index[prevIndex]) - verticies->at(index[actualIndex]), verticies->at(index[nextIndex])- verticies->at(index[actualIndex])).length();
	if (!inside && 0 < convex)
	{

		indicies->push_back(index[prevIndex]);
		indicies->push_back(index[actualIndex]);
		indicies->push_back(index[nextIndex]);
		index.erase(index.begin() + actualIndex);
		prevIndex = prevIndex % index.size();
		actualIndex = actualIndex % index.size();
		nextIndex = (nextIndex) % index.size();
		return true;
	}
	else
	{
		//Next points
		prevIndex = actualIndex;
		actualIndex = nextIndex;
		nextIndex = (nextIndex + 1) % index.size();
		return false;
	}
}


/// <summary>
/// Make steps until new triangle is created
/// </summary>
void EarClippingTriangulator::NextTriangle()
{
	while (index.size() > 2 && !Step());
}

/// <summary>
/// triangulate whole polygon
/// </summary>
void EarClippingTriangulator::Triangulate()
{
	while (index.size() > 2) {
		NextTriangle();
	}
}

void EarClippingTriangulator::Reset() {
	bool clockwise = ClockwiseTest();
	index.clear();
	if (clockwise)
	{
		for (int i = 0; i < verticies->size(); i++)
		{
			index.push_back(((unsigned)verticies->size()) - 1 - i);
		}
	}
	else
	{
		for (int i = 0; i < verticies->size(); i++)
		{
			index.push_back((unsigned)i);
		}
	}
	actualIndex = 0;
	nextIndex = 1;
	prevIndex = ((int)verticies->size() - 1);
}
