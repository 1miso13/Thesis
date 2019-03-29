#include "ParametricModel.h"
#include "GLObject.h"

std::vector<glm::vec3> vertices = {
	/*glm::vec3(-50.0f, -50.0f, 0.0f),
	glm::vec3(50, -50.0f, 0.0f),
	glm::vec3(0.0f,  25.0f, 0.0f),
	glm::vec3(0.0f,  50.0f, 50.0f)*/
	// Front face
	glm::vec3(-1.0, -1.0,  1.0),
	glm::vec3(1.0, -1.0,  1.0),
	glm::vec3(1.0,  1.0,  1.0),
	glm::vec3(-1.0,  1.0,  1.0),

	// Back face
	glm::vec3(-1.0, -1.0, -1.0),
	glm::vec3(-1.0,  1.0, -1.0),
	glm::vec3(1.0,  1.0, -1.0),
	glm::vec3(1.0, -1.0, -1.0),

	// Top face
	glm::vec3(-1.0,  1.0, -1.0),
	glm::vec3(-1.0,  1.0,  1.0),
	glm::vec3(1.0,  1.0,  1.0),
	glm::vec3(1.0,  1.0, -1.0),

	// Bottom face
	glm::vec3(-1.0, -1.0, -1.0),
	glm::vec3(1.0, -1.0, -1.0),
	glm::vec3(1.0, -1.0,  1.0),
	glm::vec3(-1.0, -1.0,  1.0),

	// Right face
	glm::vec3(1.0, -1.0, -1.0),
	glm::vec3(1.0,  1.0, -1.0),
	glm::vec3(1.0,  1.0,  1.0),
	glm::vec3(1.0, -1.0,  1.0),

	// Left face
	glm::vec3(-1.0, -1.0, -1.0),
	glm::vec3(-1.0, -1.0,  1.0),
	glm::vec3(-1.0,  1.0,  1.0),
	glm::vec3(-1.0,  1.0, -1.0)
};
void ParametricModel::UpdateGLObjects() {
	//remove invalid
	for (auto it = GLObjects_map.begin(); it != GLObjects_map.end();) {
		if ((ObjectMap[it->first]) == NULL) {
			it->second->glDestroy();
			delete it->second;
			it = GLObjects_map.erase(it);
		}
		else
			it++;
	}

	//add new objects and set values 
	for (auto object : Objects)
	{
		GLObject *glO;
		if ((glO = GLObjects_map[object->ObjectName]) == NULL)
		{
			glO = new GLObject();
		}
		// Testing (CPU)
		glO->vertices = vertices; //TODO object.verticies
		glO->indices =		//TODO object. indices
		{ 0, 1, 2, 0, 2, 3,   //front
		4, 5, 6, 4, 6, 7,   //right
		8, 9, 10, 8, 10, 11,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23 }; //bottom
		glO->setNeedsUpdate();
		glO->vertices;
		glO->indices;
		glO->color=glm::vec4(	object->color[0], //R
								object->color[1], //G
								object->color[2], //B
								object->color[3]);//A
		GLObjects_map[object->ObjectName] = glO;
	}

	

}

#include <fstream>
void ParametricModel::Save(std::string filePath)
{

}
void ParametricModel::Load(std::string filePath)
{
	//load whole string from file

	//send whole string to 
}