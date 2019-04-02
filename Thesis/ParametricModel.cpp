#include "pch.h"
#include "ParametricModel.h"
#include "GLObject.h"

std::vector<glm::vec3> verticesa = {
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
void ParametricModel::RemoveAllGLObjects() {
	for (auto it = GLObjects_map.begin(); it != GLObjects_map.end();) {
			it->second->glDestroy();
			delete it->second;
			it = GLObjects_map.erase(it);
	}
	GLObjects_map.clear();
}
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
		glO->vertices = verticesa; //TODO object.verticies
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
#include <string>
#include <algorithm>
bool compareParamIndex(const paramRefStruct &a, const paramRefStruct &b)
{
	return a.paramindex < b.paramindex;
}
void ParametricModel::Save(std::string filePath)
{
	std::ofstream SaveFile;
	SaveFile.open(filePath);
	//for every item
	for (Operation* operation : OperationsVec)
	{
		std::string s= "";
		//operationName(objectName;parameter1:ref;param2:ref2;...,colorRRGGBBAA);
		//operation name
		s += operationType::OperationToString(operation->operationType);
		s += "(";
		//object name
		s += operation->name;
		s += ",";

		//get param ref for actual operation
		std::vector <paramRefStruct>  paramStructVec;
		paramRef.FindRefParameterByObject(operation->name, &paramStructVec);
		//sort param ref
		std::sort(paramStructVec.begin(), paramStructVec.end(), compareParamIndex);

		//parameters
		for (size_t i = 0, j = 0; i < operation->OperationParametersVec->size(); i++)
		{
			s += operation->OperationParametersVec->at(i);

			//if exists ref parameter
			if (paramStructVec.size()>j && paramStructVec[j].paramindex == i)
			{
				s += ":" + paramStructVec[j].refName;

				//next param ref
				j++;
			}
			s += ",";
		}
		//color
		s += operation->getColorHEX();
		//terminator
		s += ");\n";
		SaveFile << s;
	}
	SaveFile.close();
}
bool ParametricModel::Load(std::string filePath)
{
	std::ifstream ifs(filePath);
	//load whole string from file
	std::string s((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));;

	//send whole string to application
	return AddOperations(s);
}