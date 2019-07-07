#include "pch.h"
#include "ParametricModel.h"
#include "GLObject.h"
//TODO DELETE
//std::vector<glm::vec3> verticesa = {
//	/*glm::vec3(-50.0f, -50.0f, 0.0f),
//	glm::vec3(50, -50.0f, 0.0f),
//	glm::vec3(0.0f,  25.0f, 0.0f),
//	glm::vec3(0.0f,  50.0f, 50.0f)*/
//	// Front face
//	glm::vec3(-1.0, -1.0,  1.0),
//	glm::vec3(1.0, -1.0,  1.0),
//	glm::vec3(1.0,  1.0,  1.0),
//	glm::vec3(-1.0,  1.0,  1.0),
//
//	// Back face
//	glm::vec3(-1.0, -1.0, -1.0),
//	glm::vec3(-1.0,  1.0, -1.0),
//	glm::vec3(1.0,  1.0, -1.0),
//	glm::vec3(1.0, -1.0, -1.0),
//
//	// Top face
//	glm::vec3(-1.0,  1.0, -1.0),
//	glm::vec3(-1.0,  1.0,  1.0),
//	glm::vec3(1.0,  1.0,  1.0),
//	glm::vec3(1.0,  1.0, -1.0),
//
//	// Bottom face
//	glm::vec3(-1.0, -1.0, -1.0),
//	glm::vec3(1.0, -1.0, -1.0),
//	glm::vec3(1.0, -1.0,  1.0),
//	glm::vec3(-1.0, -1.0,  1.0),
//
//	// Right face
//	glm::vec3(1.0, -1.0, -1.0),
//	glm::vec3(1.0,  1.0, -1.0),
//	glm::vec3(1.0,  1.0,  1.0),
//	glm::vec3(1.0, -1.0,  1.0),
//
//	// Left face
//	glm::vec3(-1.0, -1.0, -1.0),
//	glm::vec3(-1.0, -1.0,  1.0),
//	glm::vec3(-1.0,  1.0,  1.0),
//	glm::vec3(-1.0,  1.0, -1.0)
//};
void ParametricModel::RemoveAllGLObjects() {
	for (auto it : renderer.GLObjects_map) {
		((GLObject*)it.second)->glDestroy();
		delete it.second;
	}
	renderer.GLObjects_map.clear();
}			
// Testing (CPU)
std::vector<float> vert = { /*-0.5f, -0.5f, 0.0f,
	0.5, -0.5f, 0.0f,
	0.0f, 0.25f, 0.0f,
	0.0f, 0.5f, 0.5f*/
}; 
std::vector<float> normals = { /*-0.5f, -0.5f, 0.0f,
	0.5, -0.5f, 0.0f,
	0.0f, 0.25f, 0.0f,
	0.0f, 0.5f, 0.5f*/
};

std::vector<unsigned int> ind = { /*0, 1, 2, 1, 2, 3 */};
void ParametricModel::UpdateGLObjects() {

	if (GLContext)
	{
		//remove invalid
		for (auto it = renderer.GLObjects_map.begin(); it != renderer.GLObjects_map.end();) {
			if ((ObjectMap[it->first]) == NULL) {
				((GLObject*)it->second)->glDestroy();
				delete it->second;
				it = renderer.GLObjects_map.erase(it);
			}
			else
				it++;
		}

		//add new objects and set values 
		for (auto object : Objects)
		{
			GLObject *glO;
			if ((glO = (GLObject*)renderer.GLObjects_map[object->ObjectName]) == NULL)
			{
				glO = new GLObject();
			}

			glO->vertices = &vert;//verticesa; //TODO object.vertices
			glO->indices = &ind;//TODO object. indices
			glO->normals = &normals;

			if (object->vertices.size())
			{
				glO->vertices = &object->vertices;
				glO->indices = &object->indices;
				glO->normals = &object->normals;
			}
			glO->setNeedsUpdate();

			if (object->GeometricType == Object::ObjectTypeEnum::POINT_ObjectType)
			{
				glO->mode = GL_POINTS;
			}
			if (object->GeometricType == Object::ObjectTypeEnum::LINE_ObjectType)
			{
				glO->mode = GL_LINES;
			}
			glO->color = glm::vec4(object->color[0]/255.0f, //R
				object->color[1] / 255.0f, //G
				object->color[2] / 255.0f, //B
				object->color[3] / 255.0f);//A
			renderer.GLObjects_map[object->ObjectName] = (void*)glO;
		}


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